#include "StraightsController.h"
#include "GameMaster.h"


StraightsController::StraightsController(GameMaster *model) : _model(model) {

}

void StraightsController::startGameButtonClicked(int seed, const bool *playerTypes) {
	_model->seedDeck(seed);
	_model->registerPlayers(playerTypes);
	_model->deal();
	_model->beginRound();
}

void StraightsController::cardClicked(int index) {
	_model->takeCurrentPlayerTurn(index);
}