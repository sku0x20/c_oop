project('coop', 'c', version : '5.0.0', default_options : ['c_std=c23'])

sds = files('libs/sds/sds.c')

src_files = run_command(['python3', 'grab_files.py', 'src'], check: true)
sources = src_files.stdout().strip().split('\n')
coop = executable(
    'coop',
    'entrypoint/coop.c', sources, sds,
    include_directories : ['src', 'libs']
)


unity = files('libs/unity/unity.c')

test_files = run_command(['python3', 'grab_files.py', 'test'], check : true)
tests = test_files.stdout().strip().split('\n')
foreach t : tests
    name = t.replace('/', '_').replace('.c', '')
    exe = executable(
        name,
        t, sources, unity, sds,
        include_directories : ['src', 'libs']
    )
    test(name, exe, suite : 'ut')
endforeach

it_files = run_command(['python3', 'grab_files.py', 'integrationTest'], check : true)
it = it_files.stdout().strip().split('\n')
foreach t : it
    name = t.replace('/', '_').replace('.c', '')
    exe = executable(
        name,
        t, sources, unity, sds,
        include_directories : ['src', 'libs']
    )
    test(name, exe, suite : 'it')
endforeach


e2e_files = run_command(['python3', 'grab_files.py', 'e2e'], check : true)
e2e_sources = e2e_files.stdout().strip().split('\n')
e2e = executable(
    'e2e',
    e2e_sources, unity, sds,
    include_directories: ['libs']
)
test(
    'e2e',
    e2e,
    suite : 'e2e',
    depends: [coop],
    args: [coop.full_path()]
)
