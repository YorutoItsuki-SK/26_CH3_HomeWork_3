#include "Items/ItemCoin.h"
#include "BeltGameState.h"

AItemCoin::AItemCoin()
{
	Score = 10;
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
