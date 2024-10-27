snake_lib = library('snake',
    sources: [
        'appContext.cpp',
        'foodContext.cpp',
        'snakeContext.cpp',
        'worldMapContext.cpp',
        'border.cpp',
        'gameContext.cpp',
        'pauseState.cpp',
        'snakeMovementHandler.cpp',
        'worldMapFrameBuilder.cpp',
        'direction.cpp',
        'gameOverState.cpp',
        'playState.cpp',
        'startupState.cpp',
        'worldPainter.cpp',
        'errorMsg.cpp',
        'gameStateController.cpp',
        'positionGenerator.cpp',
        'stateBase.cpp',
    ],
    dependencies: allegrocpp_dep,
)

snake_dep = declare_dependency(
    link_with: snake_lib,
    include_directories: '.',
)
