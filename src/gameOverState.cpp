#include <fstream>
#include "gameOverState.h"

constexpr const char* HIGHSCORES_FILE_NAME = "snake_results.dat";

using allegrocpp::Event;
using allegrocpp::KeyboardKey;

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
		StateBase(stateMachine, appContext),
		appContext(appContext),
		gameContext(gameContext) {
}

void GameOverState::onEnter() {
	initializeGameEndData();
}

void GameOverState::handleStateEvent(const Event& event) {
	if (event.isKeyReleased(KeyboardKey::Y)) {
		handleYesResponse();
		return;
	}
	if (event.isKeyReleased(KeyboardKey::N)) {
		handleNoResponse();
		return;
	}
}

void GameOverState::initializeGameEndData() {
	const auto& snakeContext = gameContext.getSnakeContext();
	auto snakeSize = snakeContext.getSnakeSize();
	auto highestScore = getHighestScoreSoFar();
	saveResult(snakeSize);
	gameEndData.highestScore = highestScore;
	gameEndData.achievedScore = snakeSize;
}

void GameOverState::drawInstructions() const {
	auto& writer = appContext.getTextWriter();
	auto snakeSize = gameEndData.achievedScore;
	auto highestScore = gameEndData.highestScore;
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

void GameOverState::frameUpdate() {
	const auto& snakeContext = gameContext.getSnakeContext();
	const auto& painter = gameContext.getPainter();
	painter.drawMap(gameContext.getWorldMapContext());
	painter.drawSnake(snakeContext);
	drawInstructions();
	painter.flushDisplay();
}
