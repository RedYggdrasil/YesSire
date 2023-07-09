// Fill out your copyright notice in the Description page of Project Settings.


#include "YesSire/Widget/YSHandWidget.h"
#include "Components/Button.h"
#include "Components/WrapBox.h"
#include "Kismet/GameplayStatics.h"
#include "RS/RS.h"
#include "YesSire/Data/YSRuleStateData.h"
#include "YesSire/GameplayFramework/YSGameState.h"
#include "YesSire/Style/YSStyleData.h"
#include "YesSire/Widget/YSCardWidget.h"

void UYSHandWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	BW_ToggleViewButton->OnClicked.AddUniqueDynamic(this, &ThisClass::OnToggleVisibility);
}

void UYSHandWidget::RedrawHand(const FYSRuleStateData& RuleData)
{
	BW_HandTile->ClearChildren();
	for (int32 i = 0; i < RuleData.Hand.Num(); ++i)
	{
		const FYSCardData& Card = RuleData.Hand[i];
		UYSCardWidget* CardWidget = CreateWidget<UYSCardWidget>(this, CardWidgetClass)->InitUObj(Card, this, i);
		UWrapBoxSlot * WrapSlot = BW_HandTile->AddChildToWrapBox(CardWidget);
	}
}

void UYSHandWidget::AnimateCard(int32 InCardIndex, double InTime)
{
	if (BW_HandTile->GetChildrenCount() > InCardIndex)
	{
		UYSCardWidget* CardWidget = Cast<UYSCardWidget>(BW_HandTile->GetChildAt(InCardIndex));
		CardWidget->SetColorAndOpacity(YSStyleI.LightActionColor);
	}
}

void UYSHandWidget::OnToggleVisibility()
{
	bool bVisible = BW_HandTile->GetVisibility() != ESlateVisibility::Hidden;

	BW_HandTile->SetVisibility(bVisible ? ESlateVisibility::Hidden : ESlateVisibility::Visible);
}

void UYSHandWidget::OnCardClicked(int32 InCardIndex)
{
	AYSGameState* GS = Cast<AYSGameState>(UGameplayStatics::GetGameState(GetWorld()));
	if (GS)
	{
		GS->ApplySelectedCard(InCardIndex);
	}
}
