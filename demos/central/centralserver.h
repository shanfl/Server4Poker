#include "ServerBase.h"
#include <map>
#include "gen_proto/Central.pb.h"
#include <random>


#define TIMERID_HEATBEAT (Base::MIN_USER_TIMERID + 1)

struct ServerInfo
{
	std::string server_name;
	int32_t server_type;
	int32_t server_index;
	std::chrono::steady_clock::time_point last_active;
};

using ServerLayout = std::map<std::pair<int32_t, int32_t>, ServerInfo>;

class Timer123 : public Base::ITimerListener, public std::enable_shared_from_this<Timer123>
{
public:

	Timer123(Base::ServerBase* base) {
		ptr = base;
		mTimerAlloc.init(ptr);
	}

	virtual int  thd_idx_timer() override
	{
		return 1 + rand() % 13;
	}

	void add_timer(int id, int delay, int interval)
	{
		mTimerAlloc.add_timer(id, delay, interval, shared_from_this());
	}

	void rem_timer(int id) {
		mTimerAlloc.rem_timer(id);
	}

	void __on_timer(int id, int d, int i) override
	{
		this->ptr->log(Base::LogLevel::info, "timerid:", std::to_string(id), ",thread:", i);
	}
	Base::ServerBase* ptr;
	Base::TimerAlloc mTimerAlloc;
};

class CentralServer :public Base::ServerBase
{
	BEGIN_MSG_MAP(CentralServer, Base::ServerBase)
		BIND_NATS_MSG(Pb::Central, ID_RegisterToCentral, RegisterToCentral)
	END_MSG_MAP()

	virtual bool post_init(const toml::Value& root) override;

	virtual void on_timer(int timerid, int interval) override;
protected:
	void on_natspub_RegisterToCentral(Base::NatsClinetPtr nats, Base::Message& msg);

	void pub_ServerInfo(Base::NatsClinetPtr natss);
public:
	ServerLayout mServerLayout;
	std::shared_mutex mMutexServerLayout;

	std::vector<std::shared_ptr<Timer123>> mTimers;
};
