#include <benchmark/benchmark.h>
#include <vector>
#include <thread>
#include <future>
static auto constexpr THREAD_NUM = 10;
static const std::string RANDOM_STR = "2wbh9PqY7v9lSc4O12hWbJ73IMj9eVQ0HmA8F4LmDVgblD94BHV6jJcYD90t"
                                      "al4D1zgSRZXcTZqSIA2NQFiAkNiZRZpfu0pPUduYGZXbYiIq0ewBAN9JgQOaaRI"
                                      "Hhg6nMHVDCuUYXta7SaKdJwyKxPm1yxfM420KicCp7tDRwigUKQwnmCo4VdAtUqo"
                                      "OaTg1iNcFTjCvtRLj7kCRtGKp1OVwj9PM7axwkP4M7IonhKFk7ibnewt2zvUOYx6eqNm"
                                      "RrIGgt3OGkCxVDBz4dBF4kHV6p8NS5xhUVCQdnW19iYPO5olVv19qN7SHqGskG1x"
                                      "UbRI9JF1QfdeNoiLBLmntI5bRzDJ0uEq3IJlkvyaEeEi5OWMIlY21zwEJ2g05wsQ"
                                      "vAvAnmp7mev06vctjccszCJkcPDQcOgwEbHob4NgPT1sIq0XRxy8ksIlBwcUhA12g6"
                                      "vtTGNOewEReW9rcKOIcXHBjBKxBZxsn4QfDrKD0kBEVYeRCmCWaHO9saMO07xPS"
                                      "yjQuNK3ZXXfx3XvmbUF77r3TO9Aa73oK4yeoTYYxeZF69LebcpFN2woQDb02HMft"
                                      "ACZvgbsL5bO1ieHWwb4DXbnECwtMkhcsulu42SvSIYceNxwV6ShfwI2b6thBjn"
                                      "B4u3dh2Vzq8wL2503JWVlBWbPNnIlGO0aUAHDgT0pwET9gAzwiHEreNUKcPahYE4"
                                      "D9gU27dfb5OAWPJJIrvcANMb4mSC9MGp4ZRMW07hHF9DwPiiMoGprlVBeUOjqlH"
                                      "EXNzES5YccbyN0iWapAwKjaGt3ej6nt0YAGGKq4cvEzEv7AVnVvQlzwIbULU3dT"
                                      "jPGbLGzFEtvfCwm42BipgERTsDooM7C7BfP91YmMDZSQp1BAC0fDu6eVTTbJoTl"
                                      "FFPaWhaDORkdtoqBiTalfvmDkowG81O14yxH1enONpjQfWC54pE6yGsKUWi30mp4"
                                      "3eWxbXFRuqGYPGtZzeJUPADPk7YNLHm17bPLVjJiXJiRe"
                                      "2wbh9PqY7v9lSc4O12hWbJ73IMj9eVQ0HmA8F4LmDVgblD94BHV6jJcYD90t"
                                      "al4D1zgSRZXcTZqSIA2NQFiAkNiZRZpfu0pPUduYGZXbYiIq0ewBAN9JgQOaaRI"
                                      "Hhg6nMHVDCuUYXta7SaKdJwyKxPm1yxfM420KicCp7tDRwigUKQwnmCo4VdAtUqo"
                                      "OaTg1iNcFTjCvtRLj7kCRtGKp1OVwj9PM7axwkP4M7IonhKFk7ibnewt2zvUOYx6eqNm"
                                      "RrIGgt3OGkCxVDBz4dBF4kHV6p8NS5xhUVCQdnW19iYPO5olVv19qN7SHqGskG1x"
                                      "UbRI9JF1QfdeNoiLBLmntI5bRzDJ0uEq3IJlkvyaEeEi5OWMIlY21zwEJ2g05wsQ"
                                      "vAvAnmp7mev06vctjccszCJkcPDQcOgwEbHob4NgPT1sIq0XRxy8ksIlBwcUhA12g6"
                                      "vtTGNOewEReW9rcKOIcXHBjBKxBZxsn4QfDrKD0kBEVYeRCmCWaHO9saMO07xPS"
                                      "yjQuNK3ZXXfx3XvmbUF77r3TO9Aa73oK4yeoTYYxeZF69LebcpFN2woQDb02HMft"
                                      "ACZvgbsL5bO1ieHWwb4DXbnECwtMkhcsulu42SvSIYceNxwV6ShfwI2b6thBjn"
                                      "B4u3dh2Vzq8wL2503JWVlBWbPNnIlGO0aUAHDgT0pwET9gAzwiHEreNUKcPahYE4"
                                      "D9gU27dfb5OAWPJJIrvcANMb4mSC9MGp4ZRMW07hHF9DwPiiMoGprlVBeUOjqlH"
                                      "EXNzES5YccbyN0iWapAwKjaGt3ej6nt0YAGGKq4cvEzEv7AVnVvQlzwIbULU3dT"
                                      "jPGbLGzFEtvfCwm42BipgERTsDooM7C7BfP91YmMDZSQp1BAC0fDu6eVTTbJoTl"
                                      "FFPaWhaDORkdtoqBiTalfvmDkowG81O14yxH1enONpjQfWC54pE6yGsKUWi30mp4"
                                      "3eWxbXFRuqGYPGtZzeJUPADPk7YNLHm17bPLVjJiXJiRe"
                                      "2wbh9PqY7v9lSc4O12hWbJ73IMj9eVQ0HmA8F4LmDVgblD94BHV6jJcYD90t"
                                      "al4D1zgSRZXcTZqSIA2NQFiAkNiZRZpfu0pPUduYGZXbYiIq0ewBAN9JgQOaaRI"
                                      "Hhg6nMHVDCuUYXta7SaKdJwyKxPm1yxfM420KicCp7tDRwigUKQwnmCo4VdAtUqo"
                                      "OaTg1iNcFTjCvtRLj7kCRtGKp1OVwj9PM7axwkP4M7IonhKFk7ibnewt2zvUOYx6eqNm"
                                      "RrIGgt3OGkCxVDBz4dBF4kHV6p8NS5xhUVCQdnW19iYPO5olVv19qN7SHqGskG1x"
                                      "UbRI9JF1QfdeNoiLBLmntI5bRzDJ0uEq3IJlkvyaEeEi5OWMIlY21zwEJ2g05wsQ"
                                      "vAvAnmp7mev06vctjccszCJkcPDQcOgwEbHob4NgPT1sIq0XRxy8ksIlBwcUhA12g6"
                                      "vtTGNOewEReW9rcKOIcXHBjBKxBZxsn4QfDrKD0kBEVYeRCmCWaHO9saMO07xPS"
                                      "yjQuNK3ZXXfx3XvmbUF77r3TO9Aa73oK4yeoTYYxeZF69LebcpFN2woQDb02HMft"
                                      "ACZvgbsL5bO1ieHWwb4DXbnECwtMkhcsulu42SvSIYceNxwV6ShfwI2b6thBjn"
                                      "B4u3dh2Vzq8wL2503JWVlBWbPNnIlGO0aUAHDgT0pwET9gAzwiHEreNUKcPahYE4"
                                      "D9gU27dfb5OAWPJJIrvcANMb4mSC9MGp4ZRMW07hHF9DwPiiMoGprlVBeUOjqlH"
                                      "EXNzES5YccbyN0iWapAwKjaGt3ej6nt0YAGGKq4cvEzEv7AVnVvQlzwIbULU3dT"
                                      "jPGbLGzFEtvfCwm42BipgERTsDooM7C7BfP91YmMDZSQp1BAC0fDu6eVTTbJoTl"
                                      "FFPaWhaDORkdtoqBiTalfvmDkowG81O14yxH1enONpjQfWC54pE6yGsKUWi30mp4"
                                      "3eWxbXFRuqGYPGtZzeJUPADPk7YNLHm17bPLVjJiXJiRe"
                                      "2wbh9PqY7v9lSc4O12hWbJ73IMj9eVQ0HmA8F4LmDVgblD94BHV6jJcYD90t"
                                      "al4D1zgSRZXcTZqSIA2NQFiAkNiZRZpfu0pPUduYGZXbYiIq0ewBAN9JgQOaaRI"
                                      "Hhg6nMHVDCuUYXta7SaKdJwyKxPm1yxfM420KicCp7tDRwigUKQwnmCo4VdAtUqo"
                                      "OaTg1iNcFTjCvtRLj7kCRtGKp1OVwj9PM7axwkP4M7IonhKFk7ibnewt2zvUOYx6eqNm"
                                      "RrIGgt3OGkCxVDBz4dBF4kHV6p8NS5xhUVCQdnW19iYPO5olVv19qN7SHqGskG1x"
                                      "UbRI9JF1QfdeNoiLBLmntI5bRzDJ0uEq3IJlkvyaEeEi5OWMIlY21zwEJ2g05wsQ"
                                      "vAvAnmp7mev06vctjccszCJkcPDQcOgwEbHob4NgPT1sIq0XRxy8ksIlBwcUhA12g6"
                                      "vtTGNOewEReW9rcKOIcXHBjBKxBZxsn4QfDrKD0kBEVYeRCmCWaHO9saMO07xPS"
                                      "yjQuNK3ZXXfx3XvmbUF77r3TO9Aa73oK4yeoTYYxeZF69LebcpFN2woQDb02HMft"
                                      "ACZvgbsL5bO1ieHWwb4DXbnECwtMkhcsulu42SvSIYceNxwV6ShfwI2b6thBjn"
                                      "B4u3dh2Vzq8wL2503JWVlBWbPNnIlGO0aUAHDgT0pwET9gAzwiHEreNUKcPahYE4"
                                      "D9gU27dfb5OAWPJJIrvcANMb4mSC9MGp4ZRMW07hHF9DwPiiMoGprlVBeUOjqlH"
                                      "EXNzES5YccbyN0iWapAwKjaGt3ej6nt0YAGGKq4cvEzEv7AVnVvQlzwIbULU3dT"
                                      "jPGbLGzFEtvfCwm42BipgERTsDooM7C7BfP91YmMDZSQp1BAC0fDu6eVTTbJoTl"
                                      "FFPaWhaDORkdtoqBiTalfvmDkowG81O14yxH1enONpjQfWC54pE6yGsKUWi30mp4"
                                      "3eWxbXFRuqGYPGtZzeJUPADPk7YNLHm17bPLVjJiXJiRe"
                                      "2wbh9PqY7v9lSc4O12hWbJ73IMj9eVQ0HmA8F4LmDVgblD94BHV6jJcYD90t"
                                      "al4D1zgSRZXcTZqSIA2NQFiAkNiZRZpfu0pPUduYGZXbYiIq0ewBAN9JgQOaaRI"
                                      "Hhg6nMHVDCuUYXta7SaKdJwyKxPm1yxfM420KicCp7tDRwigUKQwnmCo4VdAtUqo"
                                      "OaTg1iNcFTjCvtRLj7kCRtGKp1OVwj9PM7axwkP4M7IonhKFk7ibnewt2zvUOYx6eqNm"
                                      "RrIGgt3OGkCxVDBz4dBF4kHV6p8NS5xhUVCQdnW19iYPO5olVv19qN7SHqGskG1x"
                                      "UbRI9JF1QfdeNoiLBLmntI5bRzDJ0uEq3IJlkvyaEeEi5OWMIlY21zwEJ2g05wsQ"
                                      "vAvAnmp7mev06vctjccszCJkcPDQcOgwEbHob4NgPT1sIq0XRxy8ksIlBwcUhA12g6"
                                      "vtTGNOewEReW9rcKOIcXHBjBKxBZxsn4QfDrKD0kBEVYeRCmCWaHO9saMO07xPS"
                                      "yjQuNK3ZXXfx3XvmbUF77r3TO9Aa73oK4yeoTYYxeZF69LebcpFN2woQDb02HMft"
                                      "ACZvgbsL5bO1ieHWwb4DXbnECwtMkhcsulu42SvSIYceNxwV6ShfwI2b6thBjn"
                                      "B4u3dh2Vzq8wL2503JWVlBWbPNnIlGO0aUAHDgT0pwET9gAzwiHEreNUKcPahYE4"
                                      "D9gU27dfb5OAWPJJIrvcANMb4mSC9MGp4ZRMW07hHF9DwPiiMoGprlVBeUOjqlH"
                                      "EXNzES5YccbyN0iWapAwKjaGt3ej6nt0YAGGKq4cvEzEv7AVnVvQlzwIbULU3dT"
                                      "jPGbLGzFEtvfCwm42BipgERTsDooM7C7BfP91YmMDZSQp1BAC0fDu6eVTTbJoTl"
                                      "FFPaWhaDORkdtoqBiTalfvmDkowG81O14yxH1enONpjQfWC54pE6yGsKUWi30mp4"
                                      "3eWxbXFRuqGYPGtZzeJUPADPk7YNLHm17bPLVjJiXJiRe"
                                      "2wbh9PqY7v9lSc4O12hWbJ73IMj9eVQ0HmA8F4LmDVgblD94BHV6jJcYD90t"
                                      "al4D1zgSRZXcTZqSIA2NQFiAkNiZRZpfu0pPUduYGZXbYiIq0ewBAN9JgQOaaRI"
                                      "Hhg6nMHVDCuUYXta7SaKdJwyKxPm1yxfM420KicCp7tDRwigUKQwnmCo4VdAtUqo"
                                      "OaTg1iNcFTjCvtRLj7kCRtGKp1OVwj9PM7axwkP4M7IonhKFk7ibnewt2zvUOYx6eqNm"
                                      "RrIGgt3OGkCxVDBz4dBF4kHV6p8NS5xhUVCQdnW19iYPO5olVv19qN7SHqGskG1x"
                                      "UbRI9JF1QfdeNoiLBLmntI5bRzDJ0uEq3IJlkvyaEeEi5OWMIlY21zwEJ2g05wsQ"
                                      "vAvAnmp7mev06vctjccszCJkcPDQcOgwEbHob4NgPT1sIq0XRxy8ksIlBwcUhA12g6"
                                      "vtTGNOewEReW9rcKOIcXHBjBKxBZxsn4QfDrKD0kBEVYeRCmCWaHO9saMO07xPS"
                                      "yjQuNK3ZXXfx3XvmbUF77r3TO9Aa73oK4yeoTYYxeZF69LebcpFN2woQDb02HMft"
                                      "ACZvgbsL5bO1ieHWwb4DXbnECwtMkhcsulu42SvSIYceNxwV6ShfwI2b6thBjn"
                                      "B4u3dh2Vzq8wL2503JWVlBWbPNnIlGO0aUAHDgT0pwET9gAzwiHEreNUKcPahYE4"
                                      "D9gU27dfb5OAWPJJIrvcANMb4mSC9MGp4ZRMW07hHF9DwPiiMoGprlVBeUOjqlH"
                                      "EXNzES5YccbyN0iWapAwKjaGt3ej6nt0YAGGKq4cvEzEv7AVnVvQlzwIbULU3dT"
                                      "jPGbLGzFEtvfCwm42BipgERTsDooM7C7BfP91YmMDZSQp1BAC0fDu6eVTTbJoTl"
                                      "FFPaWhaDORkdtoqBiTalfvmDkowG81O14yxH1enONpjQfWC54pE6yGsKUWi30mp4"
                                      "3eWxbXFRuqGYPGtZzeJUPADPk7YNLHm17bPLVjJiXJiRe"
                                      "2wbh9PqY7v9lSc4O12hWbJ73IMj9eVQ0HmA8F4LmDVgblD94BHV6jJcYD90t"
                                      "al4D1zgSRZXcTZqSIA2NQFiAkNiZRZpfu0pPUduYGZXbYiIq0ewBAN9JgQOaaRI"
                                      "Hhg6nMHVDCuUYXta7SaKdJwyKxPm1yxfM420KicCp7tDRwigUKQwnmCo4VdAtUqo"
                                      "OaTg1iNcFTjCvtRLj7kCRtGKp1OVwj9PM7axwkP4M7IonhKFk7ibnewt2zvUOYx6eqNm"
                                      "RrIGgt3OGkCxVDBz4dBF4kHV6p8NS5xhUVCQdnW19iYPO5olVv19qN7SHqGskG1x"
                                      "UbRI9JF1QfdeNoiLBLmntI5bRzDJ0uEq3IJlkvyaEeEi5OWMIlY21zwEJ2g05wsQ"
                                      "vAvAnmp7mev06vctjccszCJkcPDQcOgwEbHob4NgPT1sIq0XRxy8ksIlBwcUhA12g6"
                                      "vtTGNOewEReW9rcKOIcXHBjBKxBZxsn4QfDrKD0kBEVYeRCmCWaHO9saMO07xPS"
                                      "yjQuNK3ZXXfx3XvmbUF77r3TO9Aa73oK4yeoTYYxeZF69LebcpFN2woQDb02HMft"
                                      "ACZvgbsL5bO1ieHWwb4DXbnECwtMkhcsulu42SvSIYceNxwV6ShfwI2b6thBjn"
                                      "B4u3dh2Vzq8wL2503JWVlBWbPNnIlGO0aUAHDgT0pwET9gAzwiHEreNUKcPahYE4"
                                      "D9gU27dfb5OAWPJJIrvcANMb4mSC9MGp4ZRMW07hHF9DwPiiMoGprlVBeUOjqlH"
                                      "EXNzES5YccbyN0iWapAwKjaGt3ej6nt0YAGGKq4cvEzEv7AVnVvQlzwIbULU3dT"
                                      "jPGbLGzFEtvfCwm42BipgERTsDooM7C7BfP91YmMDZSQp1BAC0fDu6eVTTbJoTl"
                                      "FFPaWhaDORkdtoqBiTalfvmDkowG81O14yxH1enONpjQfWC54pE6yGsKUWi30mp4"
                                      "3eWxbXFRuqGYPGtZzeJUPADPk7YNLHm17bPLVjJiXJiRe"
                                      "2wbh9PqY7v9lSc4O12hWbJ73IMj9eVQ0HmA8F4LmDVgblD94BHV6jJcYD90t"
                                      "al4D1zgSRZXcTZqSIA2NQFiAkNiZRZpfu0pPUduYGZXbYiIq0ewBAN9JgQOaaRI"
                                      "Hhg6nMHVDCuUYXta7SaKdJwyKxPm1yxfM420KicCp7tDRwigUKQwnmCo4VdAtUqo"
                                      "OaTg1iNcFTjCvtRLj7kCRtGKp1OVwj9PM7axwkP4M7IonhKFk7ibnewt2zvUOYx6eqNm"
                                      "RrIGgt3OGkCxVDBz4dBF4kHV6p8NS5xhUVCQdnW19iYPO5olVv19qN7SHqGskG1x"
                                      "UbRI9JF1QfdeNoiLBLmntI5bRzDJ0uEq3IJlkvyaEeEi5OWMIlY21zwEJ2g05wsQ"
                                      "vAvAnmp7mev06vctjccszCJkcPDQcOgwEbHob4NgPT1sIq0XRxy8ksIlBwcUhA12g6"
                                      "vtTGNOewEReW9rcKOIcXHBjBKxBZxsn4QfDrKD0kBEVYeRCmCWaHO9saMO07xPS"
                                      "yjQuNK3ZXXfx3XvmbUF77r3TO9Aa73oK4yeoTYYxeZF69LebcpFN2woQDb02HMft"
                                      "ACZvgbsL5bO1ieHWwb4DXbnECwtMkhcsulu42SvSIYceNxwV6ShfwI2b6thBjn"
                                      "B4u3dh2Vzq8wL2503JWVlBWbPNnIlGO0aUAHDgT0pwET9gAzwiHEreNUKcPahYE4"
                                      "D9gU27dfb5OAWPJJIrvcANMb4mSC9MGp4ZRMW07hHF9DwPiiMoGprlVBeUOjqlH"
                                      "EXNzES5YccbyN0iWapAwKjaGt3ej6nt0YAGGKq4cvEzEv7AVnVvQlzwIbULU3dT"
                                      "jPGbLGzFEtvfCwm42BipgERTsDooM7C7BfP91YmMDZSQp1BAC0fDu6eVTTbJoTl"
                                      "FFPaWhaDORkdtoqBiTalfvmDkowG81O14yxH1enONpjQfWC54pE6yGsKUWi30mp4"
                                      "3eWxbXFRuqGYPGtZzeJUPADPk7YNLHm17bPLVjJiXJiRe"
                                      "2wbh9PqY7v9lSc4O12hWbJ73IMj9eVQ0HmA8F4LmDVgblD94BHV6jJcYD90t"
                                      "al4D1zgSRZXcTZqSIA2NQFiAkNiZRZpfu0pPUduYGZXbYiIq0ewBAN9JgQOaaRI"
                                      "Hhg6nMHVDCuUYXta7SaKdJwyKxPm1yxfM420KicCp7tDRwigUKQwnmCo4VdAtUqo"
                                      "OaTg1iNcFTjCvtRLj7kCRtGKp1OVwj9PM7axwkP4M7IonhKFk7ibnewt2zvUOYx6eqNm"
                                      "RrIGgt3OGkCxVDBz4dBF4kHV6p8NS5xhUVCQdnW19iYPO5olVv19qN7SHqGskG1x"
                                      "UbRI9JF1QfdeNoiLBLmntI5bRzDJ0uEq3IJlkvyaEeEi5OWMIlY21zwEJ2g05wsQ"
                                      "vAvAnmp7mev06vctjccszCJkcPDQcOgwEbHob4NgPT1sIq0XRxy8ksIlBwcUhA12g6"
                                      "vtTGNOewEReW9rcKOIcXHBjBKxBZxsn4QfDrKD0kBEVYeRCmCWaHO9saMO07xPS"
                                      "yjQuNK3ZXXfx3XvmbUF77r3TO9Aa73oK4yeoTYYxeZF69LebcpFN2woQDb02HMft"
                                      "ACZvgbsL5bO1ieHWwb4DXbnECwtMkhcsulu42SvSIYceNxwV6ShfwI2b6thBjn"
                                      "B4u3dh2Vzq8wL2503JWVlBWbPNnIlGO0aUAHDgT0pwET9gAzwiHEreNUKcPahYE4"
                                      "D9gU27dfb5OAWPJJIrvcANMb4mSC9MGp4ZRMW07hHF9DwPiiMoGprlVBeUOjqlH"
                                      "EXNzES5YccbyN0iWapAwKjaGt3ej6nt0YAGGKq4cvEzEv7AVnVvQlzwIbULU3dT"
                                      "jPGbLGzFEtvfCwm42BipgERTsDooM7C7BfP91YmMDZSQp1BAC0fDu6eVTTbJoTl"
                                      "FFPaWhaDORkdtoqBiTalfvmDkowG81O14yxH1enONpjQfWC54pE6yGsKUWi30mp4"
                                      "3eWxbXFRuqGYPGtZzeJUPADPk7YNLHm17bPLVjJiXJiRe"
                                      "2wbh9PqY7v9lSc4O12hWbJ73IMj9eVQ0HmA8F4LmDVgblD94BHV6jJcYD90t"
                                      "al4D1zgSRZXcTZqSIA2NQFiAkNiZRZpfu0pPUduYGZXbYiIq0ewBAN9JgQOaaRI"
                                      "Hhg6nMHVDCuUYXta7SaKdJwyKxPm1yxfM420KicCp7tDRwigUKQwnmCo4VdAtUqo"
                                      "OaTg1iNcFTjCvtRLj7kCRtGKp1OVwj9PM7axwkP4M7IonhKFk7ibnewt2zvUOYx6eqNm"
                                      "RrIGgt3OGkCxVDBz4dBF4kHV6p8NS5xhUVCQdnW19iYPO5olVv19qN7SHqGskG1x"
                                      "UbRI9JF1QfdeNoiLBLmntI5bRzDJ0uEq3IJlkvyaEeEi5OWMIlY21zwEJ2g05wsQ"
                                      "vAvAnmp7mev06vctjccszCJkcPDQcOgwEbHob4NgPT1sIq0XRxy8ksIlBwcUhA12g6"
                                      "vtTGNOewEReW9rcKOIcXHBjBKxBZxsn4QfDrKD0kBEVYeRCmCWaHO9saMO07xPS"
                                      "yjQuNK3ZXXfx3XvmbUF77r3TO9Aa73oK4yeoTYYxeZF69LebcpFN2woQDb02HMft"
                                      "ACZvgbsL5bO1ieHWwb4DXbnECwtMkhcsulu42SvSIYceNxwV6ShfwI2b6thBjn"
                                      "B4u3dh2Vzq8wL2503JWVlBWbPNnIlGO0aUAHDgT0pwET9gAzwiHEreNUKcPahYE4"
                                      "D9gU27dfb5OAWPJJIrvcANMb4mSC9MGp4ZRMW07hHF9DwPiiMoGprlVBeUOjqlH"
                                      "EXNzES5YccbyN0iWapAwKjaGt3ej6nt0YAGGKq4cvEzEv7AVnVvQlzwIbULU3dT"
                                      "jPGbLGzFEtvfCwm42BipgERTsDooM7C7BfP91YmMDZSQp1BAC0fDu6eVTTbJoTl"
                                      "FFPaWhaDORkdtoqBiTalfvmDkowG81O14yxH1enONpjQfWC54pE6yGsKUWi30mp4"
                                      "3eWxbXFRuqGYPGtZzeJUPADPk7YNLHm17bPLVjJiXJiRe";

void iterateOverString()
{
    std::vector<char> list;
    benchmark::DoNotOptimize(list.data());
    for(std::size_t i=0;i<RANDOM_STR.size();++i)
    {
        list.push_back(RANDOM_STR[i]);
    }
    benchmark::ClobberMemory();
}

void doItByThread()
{
    std::vector<std::thread> list;
    for(std::size_t i=0;i<THREAD_NUM;++i)
    {
        list.push_back(std::thread(iterateOverString));
    }
    for(auto &item: list)
    {
        if(item.joinable())
            item.join();
    }
}

void doItByAsyncDefault()
{
    std::vector<std::future<void>> list;
    for(std::size_t i=0;i<THREAD_NUM;++i)
    {
        list.push_back(std::async(iterateOverString));
    }
    for(auto &item: list)
    {
        item.wait();
    }
}
void doItByAsync(std::launch launchPolicy )
{
    std::vector<std::future<void>> list;
    for(std::size_t i=0;i<THREAD_NUM;++i)
    {
        list.push_back(std::async(launchPolicy, iterateOverString));
    }
    for(auto &item: list)
    {
        item.wait();
    }
}

static void threadIt(benchmark::State& state) {
  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
      doItByThread();
  }
}
BENCHMARK(threadIt);

static void asyncItDefault(benchmark::State& state) {
  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
      doItByAsyncDefault();
  }
}
BENCHMARK(asyncItDefault);

static void asyncItDeffered(benchmark::State& state) {
  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
      doItByAsync(std::launch::deferred);
  }
}
BENCHMARK(asyncItDeffered);

static void asyncItAsync(benchmark::State& state) {
  // Perform setup here
  for (auto _ : state) {
    // This code gets timed
      doItByAsync(std::launch::async);
  }
}
BENCHMARK(asyncItAsync);

// Run the benchmark
BENCHMARK_MAIN();
