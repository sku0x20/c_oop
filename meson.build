project('coop', 'c', version: '0.0.1')

src_files = run_command(['python3', 'grab_files.py', 'src'], check: true)
sources = src_files.stdout().strip().split('\n')
executable(
    'spike',
    'entrypoint/spike.c',sources,
    include_directories: ['src']
)

unity = files('libs/unity/unity.c')
test_files = run_command(['python3', 'grab_files.py', 'test'], check: true)
tests = test_files.stdout().strip().split('\n')
foreach t: tests
    name = t.replace('/', '_').replace('.c', '')
    exe = executable(
        name,
        t, sources, unity,
        include_directories: ['src', 'libs']
    )
    test(name, exe)
endforeach