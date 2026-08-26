#include "Items/ItemCoin.h"
#include "BeltGameState.h"
#include "Character/BeltCharacter.h"

AItemCoin::AItemCoin()
{
	Score = 10;
	ItemName =  TEXT("코인");
	ItemDesc = FString::Printf(TEXT("%d 점수를 획득"), Score);
}

void AItemCoin::ActivateItem(AActor* Activator)
{
	ABeltGameState* GameState = Cast<ABeltGameState>(GetWorld()->GetGameState());
	if (GameState) {
		GameState->AddScore(Score);
	}
	ABeltCharacter* BeltCharacter = Cast<ABeltCharacter>(Activator);
	if (BeltCharacter) {
		BeltCharacter->UpdateOverheadScore();
	}
	Super::ActivateItem(Activator);
	Super::ReturnToPool();
}
