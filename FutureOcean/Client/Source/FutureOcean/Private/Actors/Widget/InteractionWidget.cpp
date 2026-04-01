


#include "Actors/Widget/InteractionWidget.h"
#include "Actors/Widget/FadeWidget.h"
#include "Components/WidgetSwitcher.h"

void UInteractionWidget::SetFadeAnim(bool IsFadeIn)
{
	if (IsFadeIn)
		C_FadeWidget->CustomFadeIn();
	else
		C_FadeWidget->CustomFadeOut();
}

void UInteractionWidget::SetFadeImageOp(float _op)
{
	C_FadeWidget->SetFadeImageOp(_op);
}

void UInteractionWidget::SetWidgetSwitcherIndex(int _index)
{
	C_WidgetSwitcher->SetActiveWidgetIndex(_index);
}
