// Fill out your copyright notice in the Description page of Project Settings.


#include "YesSire/Widget/YSCardWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "YesSire/Data/YSCardData.h"
#include "YesSire/Widget/YSHandWidget.h"
#include "YesSire/Widget/YSValueSummaryWidget.h"

UYSCardWidget* UYSCardWidget::InitUObj(const FYSCardData& InCardData, UYSHandWidget* InHandWidget, int32 InCardIndex)
{
	HandWidget = InHandWidget;
	CardIndex = InCardIndex;
	for (const TPair<EYSResourceType, FYSActionValuesData>& Pair : InCardData.ResourceModifiers)
	{
		if (Pair.Value.YesValue != 0)
		{
			BW_OkSummary->AddInfo(Pair.Key, Pair.Value.YesValue);
		}
		if (Pair.Value.NoValue != 0)
		{
			BW_NoSummary->AddInfo(Pair.Key, Pair.Value.NoValue);
		}
		if (Pair.Value.DiscardValue != 0)
		{
			BW_DiscardSummary->AddInfo(Pair.Key, Pair.Value.DiscardValue);
		}
	}
	return this;
}

void UYSCardWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	BW_CardButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnCardClicked);
}

void UYSCardWidget::OnCardClicked()
{
	if (HandWidget)
	{
		HandWidget->OnCardClicked(CardIndex);
	}
}
