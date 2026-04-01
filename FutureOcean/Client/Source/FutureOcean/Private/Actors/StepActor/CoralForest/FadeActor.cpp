


#include "Actors/StepActor/CoralForest/FadeActor.h"
#include "Manager/StepManager.h"

void AFadeActor::CallCustomFade()
{
	stepManager->Call_AnimFadeWidget(IsFadeIn);
}

void AFadeActor::Call_LastStep()
{
	stepManager->Call_LastStep();
}
