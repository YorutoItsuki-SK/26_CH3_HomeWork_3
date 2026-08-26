#include "Items/ItemCoin.h"
#include "BeltGameState.h"

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
	Super::ActivateItem(Activator);
	Super::ReturnToPool();
}
