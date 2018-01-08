#pragma once

#include "ctre/phoenix/LowLevel/MotController_LowLevel.h"
#include "ctre/phoenix/Motion/TrajectoryPoint.h"
#include "ctre/phoenix/Motion/MotionProfileStatus.h"
#include <string>
#include <stdint.h>
#include <mutex>

struct _Control_6_MotProfAddTrajPoint_t;

namespace ctre {
namespace phoenix {
namespace platform {
namespace can {

template<typename T> class txTask;
//class txTask;
}
}
}
}


namespace ctre {
namespace phoenix {
namespace motion {
namespace can {
class txJob_t;
}
}
}
}

namespace ctre {
namespace phoenix {
namespace motion {
class TrajectoryBuffer;
}
}
}

namespace ctre {
namespace phoenix {
namespace motorcontrol {
namespace lowlevel {

class MotControllerWithBuffer_LowLevel: public MotController_LowLevel {

public:
	MotControllerWithBuffer_LowLevel(int baseArbId);
	virtual ctre::phoenix::ErrorCode ClearMotionProfileTrajectories();
	virtual ctre::phoenix::ErrorCode GetMotionProfileTopLevelBufferCount(int & count);
	virtual ctre::phoenix::ErrorCode PushMotionProfileTrajectory(double position, double velocity, double headingDeg, int profileSlotSelect, bool isLastPoint, bool zeroPos);
	virtual ctre::phoenix::ErrorCode IsMotionProfileTopLevelBufferFull(bool & param);
	virtual ctre::phoenix::ErrorCode ProcessMotionProfileBuffer();
	virtual ctre::phoenix::ErrorCode GetMotionProfileStatus(int &topBufferRem,
			int &topBufferCnt,
			int &btmBufferCnt,
			bool &hasUnderrun,
			bool &isUnderrun,
			bool &activePointValid,
			bool &isLast,
			int &profileSlotSelect,
			int &outputEnable);
	virtual ctre::phoenix::ErrorCode ClearMotionProfileHasUnderrun(int timeoutMs);
	virtual ctre::phoenix::ErrorCode ChangeMotionControlFramePeriod(int periodMs);
	virtual ctre::phoenix::ErrorCode SetMotionProfileTrajectoryPeriod(int durationMs, int timeoutMs);
private:

#if 1
	/**
	 * To keep buffers from getting out of control, place a cap on the top level buffer.  Calling
	 * application can stream addition points as they are fed to Talon. Approx memory footprint is
	 * this capacity X 8 bytes.
	 */

	/** Buffer for mot prof top data. */
	ctre::phoenix::motion::TrajectoryBuffer * _motProfTopBuffer;
	/** Flow control for streaming trajectories. */
	int32_t _motProfFlowControl = -1;

	/** The mut mot prof. */
	std::mutex _mutMotProf; // use this std::unique_lock<std::mutex> lck (_mutMotProf);

	/** Frame Period of the motion profile control6 frame. */
	uint _control6PeriodMs = kDefaultControl6PeriodMs;

	/**
	 * @return the tx task that transmits Control6 (motion profile control).
	 *         If it's not scheduled, then schedule it.  This is part
	 *         of making the lazy-framing that only peforms MotionProf framing
	 *         when needed to save bandwidth.
	 */
	void GetControl6(ctre::phoenix::platform::can::txTask<uint64_t> & toFill);
	/**
	 * Caller is either pushing a new motion profile point, or is
	 * calling the Process buffer routine.  In either case check our
	 * flow control to see if we need to start sending control6.
	 */
	void ReactToMotionProfileCall();
	/**
	 * Update the NextPt signals inside the control frame given the next pt to
	 * send.
	 * @param control pointer to the CAN frame payload containing control6.  Only
	 *                the signals that serialize the next trajectory point are
	 *                updated from the contents of newPt.
	 * @param newPt point to the next trajectory that needs to be inserted into
	 *              Talon RAM.
	 */
	void CopyTrajPtIntoControl(struct _Control_6_MotProfAddTrajPoint_t *control,
			const struct _Control_6_MotProfAddTrajPoint_t *newPt);

#endif
};

} // LowLevel
} // MotorControl
} // Phoenix
} // CTRE

