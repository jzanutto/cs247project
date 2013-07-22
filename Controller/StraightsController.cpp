#include "StraightsController.h"
#include "../Model/GameMaster.h"


StraightsController::StraightsController(GameMaster *model) : _model(model) {

}

void StraightsController::startGameButtonClicked(int seed, const bool *playerTypes, const bool hardMode) {
	_model->seedDeck(seed);
	_model->registerPlayers(playerTypes, hardMode);
	_model->deal();
	_model->beginRound();
}

void StraightsController::cardClicked(int index) {
	_model->takeCurrentPlayerTurn(index);
}

void StraightsController::rageButtonClicked() {
	_model->ragequit();
}

void StraightsController::endGameButtonClicked() {
	_model->reset();
}