// By Nico233


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"


void UOverlayWidgetController::BroadcastInitialValue()
{
    Super::BroadcastInitialValue();
    
    // CastChecked can make sure pointer after cast is valid in develop environment
    const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
    
    OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
    OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
    // The function is empty in super class
    const UAuraAttributeSet* AuraAttributeSet = CastChecked<UAuraAttributeSet>(AttributeSet);
    
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetHealthAttribute())
        .AddUObject(this, &UOverlayWidgetController::HealthChanged);
    
    AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AuraAttributeSet->GetMaxHealthAttribute())
        .AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
    OnHealthChanged.Broadcast(Data.NewValue);    
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
    OnMaxHealthChanged.Broadcast(Data.NewValue);
}
