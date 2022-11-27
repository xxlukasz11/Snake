#include <fstream>
#include "gameOverState.h"

constexpr const char* HIGHSCORES_FILE_NAME = "snake_results.dat";

namespace {

int getHighestScoreSoFar() {
	std::fstream file(HIGHSCORES_FILE_NAME, std::ios::in);
	int maxValue = 0;
	for (int result; file >> result;) {
		if (result > maxValue) {
			maxValue = result;
		}
	}
	file.close();
	return maxValue;
}

void saveResult(int snakeSize) {
	std::fstream file(HIGHSCORES_FILE_NAME, std::ios::app);
	file << " " << snakeSize;
	file.close();
}

} // namespace

GameOverState::GameOverState(StateMachine& stateMachine, AppContext& appContext, GameContext& gameContext) :
		StateBase(stateMachine),
		appContext(appContext),
		gameContext(gameContext) {
}

void GameOverState::onEnter() {
	auto& snakeMovementTimer = appContext.getSnakeMovementTimer();
	snakeMovementTimer.stop();
	handleGameEnd();
}

void GameOverState::handleStateEvent(const ALLEGRO_EVENT& event) {
	if (event.type == ALLEGRO_EVENT_KEY_UP && event.keyboard.keycode == ALLEGRO_KEY_Y) {
		handleYesResponse();
		return;
	}
	if (event.type == ALLEGRO_EVENT_KEY_UP && event.keyboard.keycode == ALLEGRO_KEY_N) {
		handleNoResponse();
		return;
	}
}

void GameOverState::handleGameEnd() {
	const auto& snakeContext = gameContext.getSnakeContext();
	auto snakeSize = snakeContext.getSnakeSize();
	auto highestScore = getHighestScoreSoFar();
	saveResult(snakeSize);
	drawEndingScreen(snakeSize, highestScore);
}

void GameOverState::drawEndingScreen(int snakeSize, int highestScore) const {
	const auto& snakeContext = gameContext.getSnakeContext();
	const auto& painter = gameContext.getPainter();
	painter.drawMap(gameContext.getWorldMapContext());
	painter.drawSnake(snakeContext);
	drawInstructions(snakeSize, highestScore);
	painter.flushDisplay();
}

void GameOverState::drawInstructions(int snakeSize, int highestScore) const {
	auto& writer = appContext.getTextWriter();
	if (snakeSize == highestScore) {
		writer.writeCenterAtLine(-3, "EXCELLENT! YOU MATCHED THE RECORD!");
	} else if (snakeSize > highestScore) {
		writer.writeCenterAtLine(-3, "EXCELLENT! THAT IS THE HIGHEST SCORE!");
	} else {
		writer.writeCenterAtLine(-3, "GAME OVER");
	}

	writer.writeCenterAtLine(-2, "Snake length: " + std::to_string(snakeSize));

	if (snakeSize < highestScore) {
		writer.writeCenterAtLine(-1, "Current highscore: " + std::to_string(highestScore));
	} else if (snakeSize > highestScore) {
		writer.writeCenterAtLine(-1, "Previous highscore: " + std::to_string(highestScore));
	}

	writer.writeCenterAtLine(1, "Play again? [y/n]");
}

void GameOverState::handleYesResponse() {
	gameContext.reset();
	nextState(StateType::STARTUP);
}

void GameOverState::handleNoResponse() {
	appContext.stopApp();
}
