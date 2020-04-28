// all rights reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ConfigFile.generated.h"

/**
 * custom config file
 */
UCLASS(Blueprintable)
class MYPROJECT2_API UConfigFile : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	public:

    FString *getElement(const FString name);
    int32 getElementIndex(const FString name);

    void writeField(const FString name, const FString text);

    FString path;
    TArray<FString> data;
    bool succeed = false;

    UConfigFile();
    UConfigFile(const FObjectInitializer &whatever);

	UFUNCTION(BlueprintCallable, Category=ConfigFile)
	static UConfigFile* loadConfig(const FString in_path); //, UConfigFile &Object, bool succeed


    UFUNCTION(BlueprintCallable, Category=ConfigFile)
    void saveConfig();

	UFUNCTION(BlueprintCallable, Category=ConfigFile)
    void readBoolean(const FString name, const bool defaultValue, bool &value);

    UFUNCTION(BlueprintCallable, Category=ConfigFile)
    void writeBoolean(const FString name, const bool value);

    UFUNCTION(BlueprintCallable, Category=ConfigFile)
    void readString(const FString name, const FString defaultValue, FString &value);

    UFUNCTION(BlueprintCallable, Category=ConfigFile)
    void writeString(const FString name, const FString value);

    UFUNCTION(BlueprintCallable, Category=ConfigFile)
    void readInteger(const FString name, const int defaultValue, int &value);

    UFUNCTION(BlueprintCallable, Category=ConfigFile)
    void writeInteger(const FString name, const int value);

    UFUNCTION(BlueprintCallable, Category=ConfigFile)
    void readFloat(const FString name, const float defaultValue, float &value);

    UFUNCTION(BlueprintCallable, Category=ConfigFile)
    void writeFloat(const FString name, const float value);

};
