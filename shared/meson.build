shared_inc = include_directories('.')

###############################################################################

shared_c_stdaux = static_library(
    'c-stdaux',
    c_args: '-std=c11',
    sources: files('c-stdaux/src/c-stdaux.h'),
)

shared_c_stdaux_dep = declare_dependency(
    include_directories: shared_inc,
)

###############################################################################

shared_c_siphash = static_library(
    'c-siphash',
    include_directories: [
        include_directories('c-stdaux/src'),
    ],
    sources: 'c-siphash/src/c-siphash.c',
)

shared_c_siphash_dep = declare_dependency(
    include_directories: shared_inc,
    link_with: shared_c_siphash,
)

###############################################################################

shared_c_rbtree = static_library(
    'c-rbtree',
    c_args: '-std=c11',
    include_directories: [
        include_directories('c-stdaux/src'),
    ],
    sources: files('c-rbtree/src/c-rbtree.c',
                   'c-rbtree/src/c-rbtree.h',
                   'c-rbtree/src/c-rbtree-private.h'),
)

shared_c_rbtree_dep = declare_dependency(
    include_directories: shared_inc,
    link_with: shared_c_rbtree,
)

###############################################################################

if enable_ebpf
    shared_n_acd_bpf_files = files('n-acd/src/n-acd-bpf.c')
else
    shared_n_acd_bpf_files = files('n-acd/src/n-acd-bpf-fallback.c')
endif

shared_n_acd = static_library(
    'n-acd',
    sources: files('n-acd/src/n-acd.c',
                   'n-acd/src/n-acd.h',
                   'n-acd/src/n-acd-private.h',
                   'n-acd/src/n-acd-probe.c',
                   'n-acd/src/util/timer.c',
                   'n-acd/src/util/timer.h')
             + shared_n_acd_bpf_files,
    c_args: [
        '-D_GNU_SOURCE',
        '-DSO_ATTACH_BPF=50',
        '-std=c11',
        '-Wno-pointer-arith',
        '-Wno-vla',
    ],
    include_directories: [
        include_directories('c-stdaux/src'),
        include_directories('c-siphash/src'),
        include_directories('c-list/src'),
        include_directories('c-rbtree/src'),
    ],
    dependencies: [
        shared_c_siphash_dep,
        shared_c_rbtree_dep,
    ],
)

shared_n_acd_dep = declare_dependency(
    include_directories: shared_inc,
    link_with: shared_n_acd,
)

###############################################################################

shared_n_dhcp4 = static_library(
    'n-dhcp4',
    sources: files('n-dhcp4/src/n-dhcp4-c-connection.c',
                   'n-dhcp4/src/n-dhcp4-c-lease.c',
                   'n-dhcp4/src/n-dhcp4-c-probe.c',
                   'n-dhcp4/src/n-dhcp4-client.c',
                   'n-dhcp4/src/n-dhcp4-incoming.c',
                   'n-dhcp4/src/n-dhcp4-outgoing.c',
                   'n-dhcp4/src/n-dhcp4-private.h',
                   'n-dhcp4/src/n-dhcp4-socket.c',
                   'n-dhcp4/src/n-dhcp4.h',
                   'n-dhcp4/src/util/packet.c',
                   'n-dhcp4/src/util/packet.h',
                   'n-dhcp4/src/util/socket.c',
                   'n-dhcp4/src/util/socket.h'),
    c_args: [
        '-D_GNU_SOURCE',
        '-Wno-declaration-after-statement',
        '-Wno-pointer-arith',
    ],
    include_directories: [
        include_directories('c-list/src'),
        include_directories('c-siphash/src'),
        include_directories('c-stdaux/src'),
    ],
    dependencies: [
        shared_c_siphash_dep,
    ],
)

shared_n_dhcp4_dep = declare_dependency(
    include_directories: shared_inc,
    link_with: shared_n_dhcp4,
)

###############################################################################

version_conf = configuration_data()
version_conf.set('NM_MAJOR_VERSION', nm_major_version)
version_conf.set('NM_MINOR_VERSION', nm_minor_version)
version_conf.set('NM_MICRO_VERSION', nm_micro_version)

version_header = configure_file(
    input: 'nm-version-macros.h.in',
    output: 'nm-version-macros.h',
    configuration: version_conf,
)

shared_nm_meta_setting_c = files('nm-meta-setting.c')

shared_nm_test_utils_impl_c = files('nm-test-utils-impl.c')

shared_nm_utils_nm_vpn_plugin_utils_c = files('nm-utils/nm-vpn-plugin-utils.c')

###############################################################################

shared_nm_std_aux = static_library(
    'nm-std-aux',
    sources: files('nm-std-aux/c-list-util.c'),
    c_args: [
      '-DG_LOG_DOMAIN="@0@"'.format(libnm_name),
      '-DNETWORKMANAGER_COMPILATION=0',
    ],
    include_directories: [
        top_inc,
        shared_inc,
    ],
    dependencies: [
    ],
)

shared_nm_std_aux_dep = declare_dependency(
    link_with: shared_nm_std_aux,
    include_directories: [
        top_inc,
        shared_inc,
    ],
)

###############################################################################

shared_nm_glib_aux_c_args = [
    '-DG_LOG_DOMAIN="@0@"'.format(libnm_name),
    '-DNETWORKMANAGER_COMPILATION=(NM_NETWORKMANAGER_COMPILATION_GLIB|NM_NETWORKMANAGER_COMPILATION_WITH_GLIB_I18N_LIB)',
]

shared_nm_glib_aux = static_library(
    'nm-utils-base',
    sources: files('nm-glib-aux/nm-dbus-aux.c',
                   'nm-glib-aux/nm-dedup-multi.c',
                   'nm-glib-aux/nm-enum-utils.c',
                   'nm-glib-aux/nm-errno.c',
                   'nm-glib-aux/nm-hash-utils.c',
                   'nm-glib-aux/nm-io-utils.c',
                   'nm-glib-aux/nm-json-aux.c',
                   'nm-glib-aux/nm-keyfile-aux.c',
                   'nm-glib-aux/nm-random-utils.c',
                   'nm-glib-aux/nm-secret-utils.c',
                   'nm-glib-aux/nm-shared-utils.c',
                   'nm-glib-aux/nm-time-utils.c'),
    c_args: shared_nm_glib_aux_c_args,
    include_directories: [
        top_inc,
        shared_inc,
    ],
    dependencies: [
        glib_dep,
        shared_nm_std_aux_dep,
    ],
)

shared_nm_glib_aux_dep = declare_dependency(
    link_with: shared_nm_glib_aux,
    include_directories: [
        top_inc,
        shared_inc,
    ],
    dependencies: glib_dep,
)

###############################################################################

shared_nm_udev_aux = static_library(
    'nm-udev-aux',
    sources: files('nm-udev-aux/nm-udev-utils.c'),
    c_args: shared_nm_glib_aux_c_args,
    include_directories: [
        top_inc,
        shared_inc,
    ],
    dependencies: [
        glib_dep,
        shared_nm_glib_aux_dep,
        libudev_dep,
    ],
)

shared_nm_udev_aux_dep = declare_dependency(
    link_with: shared_nm_udev_aux,
    include_directories: [
        top_inc,
        shared_inc,
    ],
    dependencies: [
        glib_dep,
        shared_nm_glib_aux_dep,
        libudev_dep,
    ],
)

###############################################################################

libnm_systemd_shared = static_library(
  'nm-systemd-shared',
  sources: files(
    'systemd/src/basic/alloc-util.c',
    'systemd/src/basic/escape.c',
    'systemd/src/basic/env-file.c',
    'systemd/src/basic/env-util.c',
    'systemd/src/basic/ether-addr-util.c',
    'systemd/src/basic/extract-word.c',
    'systemd/src/basic/fd-util.c',
    'systemd/src/basic/fileio.c',
    'systemd/src/basic/format-util.c',
    'systemd/src/basic/fs-util.c',
    'systemd/src/basic/hash-funcs.c',
    'systemd/src/basic/hashmap.c',
    'systemd/src/basic/hexdecoct.c',
    'systemd/src/basic/hostname-util.c',
    'systemd/src/basic/in-addr-util.c',
    'systemd/src/basic/io-util.c',
    'systemd/src/basic/memory-util.c',
    'systemd/src/basic/mempool.c',
    'systemd/src/basic/parse-util.c',
    'systemd/src/basic/path-util.c',
    'systemd/src/basic/prioq.c',
    'systemd/src/basic/process-util.c',
    'systemd/src/basic/random-util.c',
    'systemd/src/basic/socket-util.c',
    'systemd/src/basic/stat-util.c',
    'systemd/src/basic/string-table.c',
    'systemd/src/basic/string-util.c',
    'systemd/src/basic/strv.c',
    'systemd/src/basic/strxcpyx.c',
    'systemd/src/basic/time-util.c',
    'systemd/src/basic/tmpfile-util.c',
    'systemd/src/basic/utf8.c',
    'systemd/src/basic/util.c',
    'systemd/src/shared/dns-domain.c',
    'systemd/nm-sd-utils-shared.c',
  ),
  include_directories: include_directories(
    'systemd/sd-adapt-shared',
    'systemd/src/basic',
    'systemd/src/shared',
  ),
  dependencies: shared_nm_glib_aux_dep,
  c_args: [
    '-DNETWORKMANAGER_COMPILATION=NM_NETWORKMANAGER_COMPILATION_SYSTEMD_SHARED',
    '-DG_LOG_DOMAIN="libnm"',
  ],
)

libnm_systemd_shared_dep = declare_dependency(
  include_directories: include_directories(
    'systemd/sd-adapt-shared',
    'systemd/src/basic',
    'systemd/src/shared',
  ),
  dependencies: [
    shared_nm_glib_aux_dep,
  ],
  link_with: [
    libnm_systemd_shared,
  ],
)

libnm_systemd_logging_stub = static_library(
  'nm-systemd-logging-stub',
  sources: files(
    'systemd/nm-logging-stub.c',
  ),
  include_directories: include_directories(
    'systemd/sd-adapt-shared',
    'systemd/src/basic',
  ),
  dependencies: shared_nm_glib_aux_dep,
  c_args: [
    '-DNETWORKMANAGER_COMPILATION=NM_NETWORKMANAGER_COMPILATION_SYSTEMD_SHARED',
    '-DG_LOG_DOMAIN="libnm"',
  ],
)

libnm_systemd_shared_no_logging_dep = declare_dependency(
  dependencies: [
    libnm_systemd_shared_dep,
  ],
  link_with: [
    libnm_systemd_logging_stub,
  ],
)

if enable_tests
  subdir('nm-utils/tests')
endif
