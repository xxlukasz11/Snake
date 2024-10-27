project('snake', 'cpp', default_options: [
    'cpp_std=c++20',
    'warning_level=3',
])

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