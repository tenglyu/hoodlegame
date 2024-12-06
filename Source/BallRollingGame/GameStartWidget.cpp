#include "GameStartWidget.h"

void UGameStartWidget::OnStartButtonClicked()
{
	OnStartButtonClickedDelegate.Broadcast();
}

void UGameStartWidget::SetTitle(FString title)
{
	if (DescriptionText)
	{
		DescriptionText->SetText(FText::FromString(title.ToUpper()));
	}
}