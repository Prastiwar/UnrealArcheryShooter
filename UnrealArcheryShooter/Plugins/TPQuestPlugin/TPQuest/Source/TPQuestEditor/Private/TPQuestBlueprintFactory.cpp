// Authored by Tomasz Piowczyk. MIT License. Repository: https://github.com/Prastiwar/TPQuestPlugin

#include "TPQuestBlueprintFactory.h"
#include "TPQuestEditor.h"
#include "KismetCompilerModule.h"
#include "KismetEditorUtilities.h"
#include "Editor/UnrealEd/Public/Kismet2/SClassPickerDialog.h"
#include "ClassFilterViewer.h"

UTPQuestBlueprintFactory::UTPQuestBlueprintFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
}

FText UTPQuestBlueprintFactory::GetDisplayName() const
{
	FText Text = Super::GetDisplayName();
	return Text.IsEmpty()
		? FText::FromName(TEXT("TPQuest Blueprint"))
		: Text;
}

bool UTPQuestBlueprintFactory::ConfigureProperties()
{
	ParentClass = nullptr;

	TSharedPtr<FClassFilterViewer> Filter = MakeShareable<FClassFilterViewer>(new FClassFilterViewer);
	Filter->DisallowedClassFlags = CLASS_Abstract | CLASS_Deprecated;
	Filter->AllowedChildrenOfClasses.Add(SupportedClass);
	
	FClassViewerInitializationOptions Options;
	Options.Mode = EClassViewerMode::ClassPicker;
	Options.ClassFilter = Filter;

	UClass* ChosenClass = nullptr;
	const bool bPressedOk = SClassPickerDialog::PickClass(TitleText, Options, ChosenClass, SupportedClass);
	if (bPressedOk)
	{
		ParentClass = ChosenClass;
	}
	return bPressedOk;
}

UObject* UTPQuestBlueprintFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	if (ParentClass && FKismetEditorUtilities::CanCreateBlueprintOfClass(ParentClass))
	{
		UClass* BlueprintClass = nullptr;
		UClass* BlueprintGeneratedClass = nullptr;
		IKismetCompilerInterface& KismetCompilerModule = FModuleManager::LoadModuleChecked<IKismetCompilerInterface>("KismetCompiler");
		KismetCompilerModule.GetBlueprintTypesForClass(ParentClass, BlueprintClass, BlueprintGeneratedClass);
		return FKismetEditorUtilities::CreateBlueprint(ParentClass, InParent, Name, BPTYPE_Normal, BlueprintClass, BlueprintGeneratedClass, CallingContext);
	}
	return nullptr;
}
