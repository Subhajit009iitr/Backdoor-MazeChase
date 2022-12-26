// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerActor.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Runtime/Core/Public/Misc/AES.h"
#include "Runtime/Core/Public/Misc/SecureHash.h"
#include "Runtime/Core/Public/Misc/Base64.h"
#include "SuperTriggerActor.h"

FString ns = TEXT("eb");

// Sets default values
ATriggerActor::ATriggerActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	CollisionBox->SetBoxExtent(FVector(32.f, 32.f, 32.f));
	CollisionBox->SetCollisionProfileName("Trigger");
	RootComponent = CollisionBox;

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ATriggerActor::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ATriggerActor::BeginPlay()
{
	Super::BeginPlay();
	key = "eb";
	ns = TEXT("eb");
	
}

// Called every frame
void ATriggerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATriggerActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	FString cpno = FString::FromInt(checkpoint);
	FString msg = "CHECKPOINT " + cpno;

	if (ns != s) {
		key = key + s;
	}

	int32 size = key.Len();
	FString strsize = FString::FromInt(size);

	ns = s;
	
	if (checkpoint == 8) {
		EndGame();
	}
}

void ATriggerActor::EndGame()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, "GAME OVER");

	FString code = TEXT("BA9AF5B1A0F0549A30B6CE6F9445133047C9B74EC7DFDE8D25506635012BBE81D75AAD8B7BE2A7AAB385BADA220F905AB5807740D3A62DE0016AE6E49C63CBD9");
	FString code2 = TEXT("C1F295084ADF520D844D09557881A90589DE4F7530FA9E5FD73501421E2C73CD2FE532C19249E2CD3A5356CFA8042C1FF036E178AB2E27957972BEF4E5B318DC");

	FString flag = Decrypt(code,key);
	FString flag2 = Decrypt(code2,key);
	FString msg = TEXT("Not the right way!!!");

	if (key.Len() < 32)
	{
		while (key.Len()<32) {
			key = key + "a";
		}
	}

	if (flag.Len() != 0 || flag2.Len() != 0) {
		if (flag.Len() != 0) {
			FString Filepath = FPaths::ConvertRelativePathToFull(FPaths::LaunchDir()) + TEXT("/flag.txt");
			bool encryptme = FFileHelper::SaveStringToFile(flag, *Filepath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_None);
		}
		else {
			FString Filepath = FPaths::ConvertRelativePathToFull(FPaths::LaunchDir()) + TEXT("/flag.txt");
			bool encryptme = FFileHelper::SaveStringToFile(flag2, *Filepath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_None);
		}
	}
	else
	{
		FString Filepath = FPaths::ConvertRelativePathToFull(FPaths::LaunchDir()) + TEXT("/flag.txt");
		bool encryptme = FFileHelper::SaveStringToFile(msg, *Filepath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_None);
	}

	key = "eb";
	ns = TEXT("eb");
}

FString ATriggerActor::Encrypt(FString InputString, FString Key)
{
	// Check inputs
	if (InputString.IsEmpty()) return "";
	if (Key.IsEmpty()) return "";

	// To split correctly final result of decryption from trash symbols
	FString SplitSymbol = "EL@$@!";
	InputString.Append(SplitSymbol);

	// We need at least 32 symbols key
	Key = FMD5::HashAnsiString(*Key);
	TCHAR* KeyTChar = Key.GetCharArray().GetData();
	ANSICHAR* KeyAnsi = (ANSICHAR*)TCHAR_TO_ANSI(KeyTChar);

	// Calculate blob size and create blob
	uint8* Blob;
	uint32 Size;

	Size = InputString.Len();
	Size = Size + (FAES::AESBlockSize - (Size % FAES::AESBlockSize));

	Blob = new uint8[Size];

	// Convert string to bytes and encrypt
	if (StringToBytes(InputString, Blob, Size)) {

		FAES::EncryptData(Blob, Size, KeyAnsi);
		InputString = FString::FromHexBlob(Blob, Size);

		delete Blob;
		return InputString;
	}

	delete Blob;
	return "";
}

FString ATriggerActor::Decrypt(FString InputString, FString Key)
{
	// Check inputs
	if (InputString.IsEmpty()) return "";
	if (Key.IsEmpty()) return "";

	// To split correctly final result of decryption from trash symbols
	FString SplitSymbol = "EL@$@!";

	// We need at least 32 symbols key
	Key = FMD5::HashAnsiString(*Key);
	TCHAR* KeyTChar = Key.GetCharArray().GetData();
	ANSICHAR* KeyAnsi = (ANSICHAR*)TCHAR_TO_ANSI(KeyTChar);

	// Calculate blob size and create blob
	uint8* Blob;
	uint32 Size;

	Size = InputString.Len();
	Size = Size + (FAES::AESBlockSize - (Size % FAES::AESBlockSize));

	Blob = new uint8[Size];

	// Convert string to bytes and decrypt
	if (FString::ToHexBlob(InputString, Blob, Size)) {

		FAES::DecryptData(Blob, Size, KeyAnsi);
		InputString = BytesToString(Blob, Size);

		// Split required data from trash
		FString LeftData;
		FString RightData;
		InputString.Split(SplitSymbol, &LeftData, &RightData, ESearchCase::CaseSensitive, ESearchDir::FromStart);
		InputString = LeftData;

		delete Blob;
		return InputString;
	}

	delete Blob;
	return "";
}