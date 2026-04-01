


#include "Manager/InteractionWidgetActor.h"
#include "Actors/Widget/InteractionWidget.h"

void AInteractionWidgetActor::Init()
{
	CustomCreateWidget();
	widgetBP->SetWidgetActor(this);
}

void AInteractionWidgetActor::Call_AnimFadeWidget(bool IsFadeIn)
{
	widgetBP->SetFadeAnim(IsFadeIn);
}

void AInteractionWidgetActor::Call_FadeImageOp(float _op)
{
	widgetBP->SetFadeImageOp(_op);
}

void AInteractionWidgetActor::Call_WidgetSwitcherIndex(int _index)
{
	widgetBP->SetWidgetSwitcherIndex(_index);
}

void AInteractionWidgetActor::CustomCreateWidget()
{
	if (C_UserWidget)
	{
		widgetBP = Cast<UInteractionWidget>(CreateWidget(GetWorld(), C_UserWidget));
		if (widgetBP)
		{
			widgetBP->AddToViewport();
		}
	}
}