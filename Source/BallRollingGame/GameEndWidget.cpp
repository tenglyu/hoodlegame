#include "GameEndWidget.h"

void UGameEndWidget::SetTimer(float time)
{
	if (TimeNumber)
	{
		FString TimeString = FString::Printf(TEXT("%.1fs"), time);
		TimeNumber->SetText(FText::FromString(TimeString));
	}
}