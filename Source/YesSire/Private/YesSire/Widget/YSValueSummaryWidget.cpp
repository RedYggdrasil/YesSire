// Fill out your copyright notice in the Description page of Project Settings.


#include "YesSire/Widget/YSValueSummaryWidget.h"
#include "Components/TextBlock.h"
#include "Components/PanelWidget.h"
#include "Components/HorizontalBox.h"
#include "RS/RS.h"
#include "YesSire/Style/YSStyleData.h"

void UYSValueSummaryWidget::AddInfo(EYSResourceType EInResourceType, int32 InValue)
{
	UTextBlock* TextBlock = GetTextBlock(EInResourceType);
	if (TextBlock)
	{
		TextBlock->SetText(FText::FromString(FString::FromInt(InValue)));
		UHorizontalBox* HBox = Cast<UHorizontalBox>(TextBlock->GetParent());
		if (HBox)
		{
			int cChild = HBox->GetChildrenCount();
			for (int i = 0; i < cChild; ++i)
			{
				UWidget* child = HBox->GetChildAt(i);
				if (child->IsA<UTextBlock>())
				{
					Cast<UTextBlock>(child)->SetColorAndOpacity(InValue > 0 ? YSStyleI.PositiveColor : YSStyleI.ErrorColor);
				}
			}
		}
	}
}

UTextBlock* UYSValueSummaryWidget::GetTextBlock(EYSResourceType EInResourceType) const
{
	switch (EInResourceType)
	{
	case EYSResourceType::Coffer:
		return BW_CofferChange;
	case EYSResourceType::Society:
		return BW_SocietyChange;
	case EYSResourceType::Ideology:
		return BW_IdeologyChange;
	case EYSResourceType::Millitary:
		return BW_MillitaryChange;
	default:
		UE_LOG(LogTemp, Error, TEXT(L_PATH "Unimplemented case '%s'"), *UEnum::GetValueAsString(EInResourceType));
		return nullptr;
	}
}
