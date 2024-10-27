project('snake', 'cpp')

allegrocpp_proj = subproject('allegro-cpp')
allegrocpp_dep = allegrocpp_proj.get_variable('allegrocpp_dep')

subdir('src')

executable('snake',
    sources: 'src/main.cpp',
    dependencies: [
        snake_dep,
        allegrocpp_dep
    ],
)