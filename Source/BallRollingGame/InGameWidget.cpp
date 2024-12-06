#include "InGameWidget.h"

void UInGameWidget::SetTimer(float time)
{
	if (TimeNumber)
	{
		FString TimeString = FString::Printf(TEXT("%.1fs"), time);
		TimeNumber->SetText(FText::FromString(TimeString));
	}
}