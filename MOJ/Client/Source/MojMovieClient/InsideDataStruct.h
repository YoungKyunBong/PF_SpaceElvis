#pragma once
#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Protocols.h"
#include "InsideDataStruct.generated.h"

UENUM(BlueprintType)
enum class ENationType : uint8
{
	Sexual_SituationOne		UMETA(DisplayName = "SexualOne"),
	Sexual_SituationTwo		UMETA(DisplayName = "SexualTwo"),
	Sexual_SituationThree	UMETA(DisplayName = "SexualThree"),
	Sexual_SituationFour	UMETA(DisplayName = "SexualFour"),
	Sexual_SituationFive	UMETA(DisplayName = "SexualFive"),
	Sexual_SituationSix		UMETA(DisplayName = "SexualSix"),
	Homy_SituationOne		UMETA(DisplayName = "HomyOne"),
	Homy_SituationTwo		UMETA(DisplayName = "HomyTwo"),
	Homy_SituationThree		UMETA(DisplayName = "HomyThree"),
	Homy_SituationFour		UMETA(DisplayName = "HomyFour"),
	Stoking_SituationOne	UMETA(DisplayName = "StokingOne"),
	Stoking_SituationTwo	UMETA(DisplayName = "StokingTwo"),
	Stoking_SituationThree	UMETA(DisplayName = "StokingThree"),
	Stoking_SituationFour	UMETA(DisplayName = "StokingFour"),
	Child_SituationOne		UMETA(DisplayName = "ChildOne"),
	Child_SituationTwo		UMETA(DisplayName = "ChildTwo"),
	Child_SituationThree	UMETA(DisplayName = "ChildThree"),
	Child_SituationFour		UMETA(DisplayName = "ChildFour"),
	Drug_SituationOne		UMETA(DisplayName = "DrugOne"),
	Drug_SituationTwo		UMETA(DisplayName = "DrugTwo"),
	Drug_SituationThree		UMETA(DisplayName = "DrugThree"),
	Drug_SituationFour		UMETA(DisplayName = "DrugFour"),
};

USTRUCT(BlueprintType)
struct FMTNATEXTTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:

	FMTNATEXTTable() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TextID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Sexual_SituationOne_Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Sexual_SituationTwo_Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Sexual_SituationThree_Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Sexual_SituationFour_Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Sexual_SituationFive_Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Sexual_SituationSix_Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Homy_SituationOne_Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Homy_SituationTwo_Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Homy_SituationThree_Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Homy_SituationFour_Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Stoking_SituationOne_Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Stoking_SituationTwo_Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Stoking_SituationThree_Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Stoking_SituationFour_Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Child_SituationOne_Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Child_SituationTwo_Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Child_SituationThree_Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Child_SituationFour_Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Drug_SituationOne_Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Drug_SituationTwo_Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Drug_SituationThree_Text;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Drug_SituationFour_Text;
};

USTRUCT(BlueprintType)
struct FMTNAMETAGTEXTTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FMTNAMETAGTEXTTable() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TextID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString KOR_Text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ENG_Text;
};

USTRUCT(BlueprintType)
struct FMTSoundTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FMTSoundTable() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SoundID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* KOR_SD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* ENG_SD;
};

USTRUCT(BlueprintType)
struct FMTTextureTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FMTTextureTable() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Alias;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Korea;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Usa;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* Japan;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UTexture2D* CN;
};

UENUM(BlueprintType)
enum class SelectButtonType : uint8
{
	Normal = 0x00,
	DoNot = 0x01,
	WrongNarr = 0x02,
	Positive = 0x03,
	Negative = 0x04,
	FeedBack = 0x05,
};

UENUM(BlueprintType)
enum class FEmojiType : uint8
{
	NoneEmotion		= 0			UMETA(DisplayName = "감정없음"),
	Fear			= 1			UMETA(DisplayName = "무서움"),
	Awe				= 2			UMETA(DisplayName = "두려움"),
	Chagrin			= 3			UMETA(DisplayName = "억울함"),
	Upset			= 4			UMETA(DisplayName = "속상함"),
	Dolor			= 5			UMETA(DisplayName = "슬픔"),
	LoneLiness		= 6			UMETA(DisplayName = "외로움"),
	Refreshing		= 7			UMETA(DisplayName = "상쾌함"),
	Comfort			= 8			UMETA(DisplayName = "편안함"),
	Enjoy			= 9			UMETA(DisplayName = "즐거움"),
	Anger			= 10		UMETA(DisplayName = "분노"),
	Petulance		= 11		UMETA(DisplayName = "짜증"),
	Helplessness	= 12		UMETA(DisplayName = "무력감"),
	Shame			= 13		UMETA(DisplayName = "수치심"),
	Guilt			= 14		UMETA(DisplayName = "죄책감"),
	Anxious			= 15		UMETA(DisplayName = "불안함"),
	Depressed		= 16		UMETA(DisplayName = "우울함"),
	Warmth			= 17		UMETA(DisplayName = "따뜻함"),
	Horror			= 18		UMETA(DisplayName = "공포"),
	Disarray		= 19		UMETA(DisplayName = "혼란"),
	Tension			= 20		UMETA(DisplayName = "긴장감"),
	Uncomfortable	= 21		UMETA(DisplayName = "불편함"),
	Interesting		= 22		UMETA(DisplayName = "흥미로움"),
	Sorry			= 23		UMETA(DisplayName = "미안함"),
	Refusal			= 24		UMETA(DisplayName = "거절감"),
	Regret			= 25		UMETA(DisplayName = "후회"),
	Heaviness		= 26		UMETA(DisplayName = "답답함"),
	Emptiness		= 27		UMETA(DisplayName = "공허감"),
	Mope			= 28		UMETA(DisplayName = "우울"),
	Surprise		= 29		UMETA(DisplayName = "놀람"),
	Tired			= 30		UMETA(DisplayName = "피곤함"),
	Burden			= 31		UMETA(DisplayName = "부담감"),
	Hunger			= 32		UMETA(DisplayName = "배고픔"),
	Betrayal		= 33		UMETA(DisplayName = "배신감"),
	Despair			= 34		UMETA(DisplayName = "절망감"),
	Suffocation		= 35		UMETA(DisplayName = "숨막힘"),
	Pressure		= 36		UMETA(DisplayName = "압박감"),
	Impact			= 37		UMETA(DisplayName = "충격"),
	Sorrow			= 38		UMETA(DisplayName = "아쉬움"),
	Discomfort		= 39		UMETA(DisplayName = "불쾌감"),
	Wariness		= 40		UMETA(DisplayName = "경계심"),
	Excitement		= 41		UMETA(DisplayName = "설렘"),
};

USTRUCT(BlueprintType)
struct FSelectButton
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString buttonText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString feedBackText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString feedBackText_Sub;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString feedBackSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	MovieSceneType movieType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	SelectButtonType buttonType = SelectButtonType::Normal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEmojiType emojiType = FEmojiType::NoneEmotion;
};

USTRUCT(BlueprintType)
struct FSelectButtonArray
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FSelectButton> InnerArray;
};

UENUM(BlueprintType)
enum class SelectButtonType_Horizon : uint8
{
	Ready = 0x00,
};

USTRUCT(BlueprintType)
struct FSelectButton_Horizon
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString buttonText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	SelectButtonType_Horizon buttonType = SelectButtonType_Horizon::Ready;
};

UENUM(BlueprintType)
enum class CheckIconType : uint8
{
	CheckStop = 0x00,
	CheckThink = 0x01,
	CheckOptions = 0x02,
	CheckPick = 0x03,
};