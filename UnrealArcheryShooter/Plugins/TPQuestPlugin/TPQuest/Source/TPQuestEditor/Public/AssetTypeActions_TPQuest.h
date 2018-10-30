// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/TPQuestPlugin

#pragma once

#include "AssetTypeActions_Base.h"
#include "TPQuestEditor.h"

class TPQUESTEDITOR_API FAssetTypeActions_TPQuest : public FAssetTypeActions_Base
{
public:
	FAssetTypeActions_TPQuest()
	{
		FText Name = FText::FromName(TEXT("TPQuest Asset"));
		FText Description = FText::FromName(TEXT("TPQuest Asset"));
		FColor Color = FColor(255, 255, 255);
	}

	virtual FText GetName() const override { return Name; }
	virtual FText GetAssetDescription(const FAssetData &AssetData) const override { return Description; }
    virtual uint32 GetCategories() override { return FTPQuestEditorModule::GetQuestCategory(); }
    virtual FColor GetTypeColor() const override { return Color; }
    virtual UClass* GetSupportedClass() const override { return SupportedClass; }

protected:
	FText Name;
	FText Description;
	FColor Color;
	UClass* SupportedClass;

};
