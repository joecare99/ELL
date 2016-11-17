# Examples of binding.gyp files for real projects:
# https://github.com/nodejs/node-gyp/wiki/%22binding.gyp%22-files-out-in-the-wild
# Very helpful discussion showing how to enable RTTI on OS X:
# https://github.com/nodejs/node-gyp/issues/26
{
    'conditions': [
        [
            'OS=="win"', 
            {
                'variables': {
                    'swig_include_path_prefix%': '../../../..',
                    'include_path_prefix%': '../../..',
                    'library_path_prefix%': '../../..',
                    'library_path_suffix%': '/Release'
                },
            }
        ],
        [
            'OS=="mac"', 
            {
                'variables': {
                    'swig_include_path_prefix%':'../../..',
                    'include_path_prefix%':'../../..',
                    'library_path_prefix%':'../../../..',
                    'library_path_suffix%': ''
                },
            }
        ],
        [
            'OS=="linux"', 
            {
                'variables': {
                    'swig_include_path_prefix%':'../../..',
                    'include_path_prefix%':'../../..',
                    'library_path_prefix%':'../../../..',
                    'library_path_suffix%': ''
                },
            }
        ]
    ],
    'targets': [
        {
            'target_name': 'emll',
            'copies' : [
                {
                    'destination': 'build',
                    'files': [
                        '<(include_path_prefix)/build/interfaces/xml/EMLLXML_wrap.xml'
                    ]    
                }                
            ],
            'dependencies': [],
            'include_dirs': [
                "<!(node -e \"require('nan')\")",
                '<(include_path_prefix)/libraries/common/include',
                '<(include_path_prefix)/libraries/data/include',
                '<(include_path_prefix)/libraries/evaluators/include',
                '<(include_path_prefix)/libraries/lossFunctions/include',
                '<(include_path_prefix)/libraries/math/include',
                '<(include_path_prefix)/libraries/model/include',
                '<(include_path_prefix)/libraries/nodes/include',
                '<(include_path_prefix)/libraries/predictors/include',
                '<(include_path_prefix)/libraries/trainers/include',
                '<(include_path_prefix)/libraries/utilities/include',
                '<(include_path_prefix)/interfaces/common/include'
            ],
            'sources': [
                '<(include_path_prefix)/build/interfaces/javascript/EMLLJAVASCRIPT_wrap.cxx'
            ],
            'link_settings': {
                'library_dirs': [
                    '<(library_path_prefix)/build/libraries/common<(library_path_suffix)',
                    '<(library_path_prefix)/build/libraries/data<(library_path_suffix)',
                    '<(library_path_prefix)/build/libraries/evaluators<(library_path_suffix)',
                    '<(library_path_prefix)/build/libraries/lossFunctions<(library_path_suffix)',
                    '<(library_path_prefix)/build/libraries/math<(library_path_suffix)',
                    '<(library_path_prefix)/build/libraries/model<(library_path_suffix)',
                    '<(library_path_prefix)/build/libraries/nodes<(library_path_suffix)',
                    '<(library_path_prefix)/build/libraries/predictors<(library_path_suffix)',
                    '<(library_path_prefix)/build/libraries/trainers<(library_path_suffix)',
                    '<(library_path_prefix)/build/libraries/utilities<(library_path_suffix)',
                ]
            },
            'conditions': [
                [
                    'OS=="win"',
                    {
                        'link_settings': {
                            'libraries': [
                                '-lcommon.lib',
                                '-ldata.lib',
                                '-levaluators.lib',                                                                
                                '-llossFunctions.lib',
                                '-lmath.lib',
                                '-lmodel.lib',
                                '-lnodes.lib',
                                '-lpredictors.lib',
                                '-ltrainers.lib',
                                '-lutilities.lib'
                            ]
                        },
                        'msvs_settings': {
                            'VCCLCompilerTool': {
                                'AdditionalOptions': [
                                    '/MD'
                                ]
                            },
                            'VCLibrarianTool': {},
                            'VCLinkerTool': {}
                        }
                    }
                ],
                [
                    'OS=="mac"',
                    {
                        'link_settings': {
                            'libraries': [
                                'libcommon.a',
                                'libdata.a',
                                'libevaluators.a',
                                'liblossFunctions.a',
                                'libmath.a',
                                'libmodel.a',
                                'libnodes.a',
                                'libpredictors.a',
                                'libtrainers.a',
                                'libutilities.a',
                            ]
                        },
                        'cflags_cc!': [
                            '-fno-rtti',
                            '-fno-exceptions'
                        ],
                        'cflags!': [
                            '-fno-exceptions'
                        ],
                        'xcode_settings': {
                            'OTHER_CPLUSPLUSFLAGS': [
                                '-std=c++14',
                                '-stdlib=libc++',
                                '-v'
                            ],
                            'OTHER_LDFLAGS': [
                                '-stdlib=libc++'
                            ],
                            'MACOSX_DEPLOYMENT_TARGET': '10.11',
                            'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
                            'GCC_ENABLE_CPP_RTTI': 'YES'
                        }
                    }
                ],
                [
                    'OS=="linux"',
                    {
                        'cflags_cc': [
                            '-std=c++1y',
                            '-fexceptions'
                        ],
                        'cflags_cc!': [
                            '-fno-rtti',
                            '-fno-exceptions'
                        ],
                        'link_settings': {
                            'libraries': [
                                'libcommon.a',
                                'libdata.a',
                                'libevaluators.a',
                                'liblossFunctions.a',
                                'libmath.a',
                                'libmodel.a',
                                'libnodes.a',
                                'libpredictors.a',
                                'libtrainers.a',
                                'libutilities.a',
                            ]
                        }
                    }
                ]
            ],
        }
    ]
}