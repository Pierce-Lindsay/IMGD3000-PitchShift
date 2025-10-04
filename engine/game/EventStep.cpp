#include "EventStep.h"
using namespace df;

EventStep::EventStep()
{
	setType(STEP_EVENT);
}

EventStep::EventStep(long long init_step_count)
{
	setType(STEP_EVENT);
	step_count = init_step_count;
}


void EventStep::setStepCount(long long new_step_count)
{
	step_count = new_step_count;
}

long long EventStep::getStepCount() const
{
	return step_count;
}