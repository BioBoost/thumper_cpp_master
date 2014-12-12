#include <unistd.h>
#include "wait.h"

namespace TRexLib{
	void wait(double seconds)
	{
		usleep((int)(seconds*1000000));
	}
}