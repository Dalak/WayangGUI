cmake_minimum_required(VERSION 2.8)

include(WayangWallet.cmake)
include(QREncode.cmake)

project(${CN_PROJECT_NAME})

execute_process(COMMAND git log -1 --pretty=format:%h
WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
OUTPUT_VARIABLE GIT_REVISION)

set(CRYPTONOTE_LIB WayangCli)
set (CMAKE_PREFIX_PATH "C:\\Qt\\Qt5.6.0\\5.6\\msvc2013_64\\")

include_directories(${CMAKE_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    src
    WayangCli/external
    WayangCli/include
    WayangCli/src)

find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)

set(Boost_USE_STATIC_LIBS ON)
if(WIN32)
  set(Boost_USE_STATIC_RUNTIME OFF)
else(WIN32)
  set(Boost_USE_STATIC_RUNTIME ON)
endif(WIN32)

find_package(Boost 1.55 REQUIRED COMPONENTS date_time filesystem program_options regex serialization system thread chrono)
if ((${Boost_MAJOR_VERSION} EQUAL 1) AND (${Boost_MINOR_VERSION} EQUAL 54))
	message(SEND_ERROR "Boost version 1.54 is unsupported, more details are available here http://goo.gl/RrCFmA")
endif ()

include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

set(VERSION "")
configure_file("WayangCli/src/version.h.in" "version.h")
configure_file("src/CryptoNoteWalletConfig.h.in" "CryptoNoteWalletConfig.h")

add_definitions(-DVERSION=\"${CN_VERSION}\")
add_definitions(-DGIT_REVISION=\"${GIT_REVISION}\")

set(CMAKE_AUTOMOC ON)

set(CRYPTONOTE_SOURCES
  WayangCli/external/miniupnpc/connecthostport.c
  WayangCli/external/miniupnpc/igd_desc_parse.c
  WayangCli/external/miniupnpc/minisoap.c
  WayangCli/external/miniupnpc/miniupnpc.c
  WayangCli/external/miniupnpc/miniwget.c
  WayangCli/external/miniupnpc/minixml.c
  WayangCli/external/miniupnpc/portlistingparse.c
  WayangCli/external/miniupnpc/receivedata.c
  WayangCli/external/miniupnpc/upnpcommands.c
  WayangCli/external/miniupnpc/upnpreplyparse.c
  WayangCli/src/Common/Base58.cpp
  WayangCli/src/Common/CommandLine.cpp
  WayangCli/src/Common/Util.cpp
  WayangCli/src/Common/StringTools.cpp
  WayangCli/src/Common/JsonValue.cpp
  WayangCli/src/Common/ConsoleTools.cpp
  WayangCli/src/Common/MemoryInputStream.cpp
  WayangCli/src/Common/PathTools.cpp
  WayangCli/src/Common/StdInputStream.cpp
  WayangCli/src/Common/StdOutputStream.cpp
  WayangCli/src/Common/StreamTools.cpp
  WayangCli/src/Common/StringOutputStream.cpp
  WayangCli/src/Common/StringView.cpp
  WayangCli/src/Common/VectorOutputStream.cpp
  WayangCli/src/crypto/blake256.c
  WayangCli/src/crypto/chacha.c
  WayangCli/src/crypto/crypto-ops-data.c
  WayangCli/src/crypto/crypto-ops.c
  WayangCli/src/crypto/crypto.cpp
  WayangCli/src/crypto/groestl.c
  WayangCli/src/crypto/hash-extra-blake.c
  WayangCli/src/crypto/hash-extra-groestl.c
  WayangCli/src/crypto/hash-extra-jh.c
  WayangCli/src/crypto/hash-extra-skein.c
  WayangCli/src/crypto/hash.c
  WayangCli/src/crypto/jh.c
  WayangCli/src/crypto/keccak.c
  WayangCli/src/crypto/oaes_lib.c
  WayangCli/src/crypto/random.c
  WayangCli/src/crypto/skein.c
  WayangCli/src/crypto/slow-hash.c
  WayangCli/src/crypto/slow-hash.cpp
  WayangCli/src/crypto/tree-hash.c
  WayangCli/src/CryptoNoteCore/BlockchainIndices.cpp
  WayangCli/src/CryptoNoteCore/BlockchainMessages.cpp
  WayangCli/src/CryptoNoteCore/BlockIndex.cpp
  WayangCli/src/CryptoNoteCore/CoreConfig.cpp
  WayangCli/src/CryptoNoteCore/CryptoNoteBasic.cpp
  WayangCli/src/CryptoNoteCore/CryptoNoteTools.cpp
  WayangCli/src/CryptoNoteCore/Currency.cpp
  WayangCli/src/CryptoNoteCore/DepositIndex.cpp
  WayangCli/src/CryptoNoteCore/MinerConfig.cpp
  WayangCli/src/CryptoNoteCore/Transaction.cpp
  WayangCli/src/CryptoNoteCore/Account.cpp
  WayangCli/src/CryptoNoteCore/Blockchain.cpp
  WayangCli/src/CryptoNoteCore/Checkpoints.cpp
  WayangCli/src/CryptoNoteCore/CryptoNoteBasicImpl.cpp
  WayangCli/src/CryptoNoteCore/Core.cpp
  WayangCli/src/CryptoNoteCore/CryptoNoteFormatUtils.cpp
  WayangCli/src/CryptoNoteCore/CryptoNoteSerialization.cpp
  WayangCli/src/CryptoNoteCore/Difficulty.cpp
  WayangCli/src/CryptoNoteCore/IBlock.cpp
  WayangCli/src/CryptoNoteCore/Miner.cpp
  WayangCli/src/CryptoNoteCore/TransactionExtra.cpp
  WayangCli/src/CryptoNoteCore/TransactionPool.cpp
  WayangCli/src/CryptoNoteCore/TransactionPrefixImpl.cpp
  WayangCli/src/CryptoNoteCore/TransactionUtils.cpp
  WayangCli/src/InProcessNode/InProcessNode.cpp
  WayangCli/src/InProcessNode/InProcessNodeErrors.cpp
  WayangCli/src/NodeRpcProxy/NodeErrors.cpp
  WayangCli/src/NodeRpcProxy/NodeRpcProxy.cpp
  WayangCli/src/P2p/NetNodeConfig.cpp
  WayangCli/src/Serialization/BinaryInputStreamSerializer.cpp
  WayangCli/src/Serialization/BinaryOutputStreamSerializer.cpp
  WayangCli/src/Serialization/JsonInputValueSerializer.cpp
  WayangCli/src/Serialization/JsonOutputStreamSerializer.cpp
  WayangCli/src/Serialization/KVBinaryInputStreamSerializer.cpp
  WayangCli/src/Serialization/KVBinaryOutputStreamSerializer.cpp
  WayangCli/src/Serialization/SerializationOverloads.cpp
  WayangCli/src/Transfers/BlockchainSynchronizer.cpp
  WayangCli/src/Transfers/SynchronizationState.cpp
  WayangCli/src/Transfers/TransfersConsumer.cpp
  WayangCli/src/Transfers/TransfersContainer.cpp
  WayangCli/src/Transfers/TransfersSubscription.cpp
  WayangCli/src/Transfers/TransfersSynchronizer.cpp
  WayangCli/src/Wallet/LegacyKeysImporter.cpp
  WayangCli/src/Wallet/WalletAsyncContextCounter.cpp
  WayangCli/src/Wallet/WalletErrors.cpp
  WayangCli/src/WalletLegacy/KeysStorage.cpp
  WayangCli/src/WalletLegacy/WalletLegacy.cpp
  WayangCli/src/WalletLegacy/WalletHelper.cpp
  WayangCli/src/WalletLegacy/WalletLegacySerializer.cpp
  WayangCli/src/WalletLegacy/WalletLegacySerialization.cpp
  WayangCli/src/WalletLegacy/WalletTransactionSender.cpp
  WayangCli/src/WalletLegacy/WalletUnconfirmedTransactions.cpp
  WayangCli/src/WalletLegacy/WalletUserTransactionsCache.cpp
  WayangCli/src/System/ContextGroup.cpp
  WayangCli/src/System/Event.cpp
  WayangCli/src/System/EventLock.cpp
  WayangCli/src/System/InterruptedException.cpp
  WayangCli/src/System/Ipv4Address.cpp
  WayangCli/src/System/TcpStream.cpp
  WayangCli/src/HTTP/HttpRequest.cpp
  WayangCli/src/HTTP/HttpParser.cpp
  WayangCli/src/HTTP/HttpParserErrorCodes.cpp
  WayangCli/src/HTTP/HttpResponse.cpp
  WayangCli/src/Rpc/HttpClient.cpp
  WayangCli/src/Rpc/JsonRpc.cpp
  WayangCli/src/P2p/NetNode.cpp
  WayangCli/src/P2p/LevinProtocol.cpp
  WayangCli/src/P2p/NetNodeConfig.cpp
  WayangCli/src/P2p/PeerListManager.cpp
  WayangCli/src/CryptoNoteProtocol/CryptoNoteProtocolHandler.cpp
  WayangCli/src/Logging/ILogger.cpp
  WayangCli/src/Logging/LoggerGroup.cpp
  WayangCli/src/Logging/CommonLogger.cpp
  WayangCli/src/Logging/LoggerManager.cpp
  WayangCli/src/Logging/FileLogger.cpp
  WayangCli/src/Logging/StreamLogger.cpp
  WayangCli/src/Logging/ConsoleLogger.cpp
  WayangCli/src/Logging/LoggerMessage.cpp
  WayangCli/src/Logging/LoggerRef.cpp
  WayangCli/src/BlockchainExplorer/BlockchainExplorer.cpp
  WayangCli/src/BlockchainExplorer/BlockchainExplorerDataBuilder.cpp
  WayangCli/src/BlockchainExplorer/BlockchainExplorerErrors.cpp
)

file(GLOB_RECURSE SOURCES src/*.cpp)
file(GLOB_RECURSE HEADERS src/*.h)
file(GLOB_RECURSE FORMS src/gui/ui/*.ui)

set(QRC src/resources.qrc)

qt5_wrap_ui(UIS ${FORMS})
qt5_add_resources(RCC ${QRC})


if (WIN32)
  if (NOT MSVC)
	message(FATAL_ERROR "Only MSVC is supported on this platform")
  endif ()
  add_definitions(/D_CRT_SECURE_NO_WARNINGS /D_WIN32_WINNT=0x0600 /DSTATICLIB)
  include_directories(WayangCli/src/platform/msc)

  set(PLATFORM_DIR Windows)
  set(BUILD_PLATFORM WIN32)
  set(BUILD_RESOURCES src/wayangwallet.rc)
  set(QTMAIN Qt5::WinMain)

elseif (UNIX)
  set(CRYPTONOTE_SOURCES ${CRYPTONOTE_SOURCES} WayangCli/external/miniupnpc/minissdpc.c)
  if (APPLE)
    enable_language(ASM)
    file(GLOB_RECURSE OBJC_SOURCES src/*.mm)
    set(SOURCES ${SOURCES} ${OBJC_SOURCES})
    set(PLATFORM_DIR OSX)
    set(MACOSX_BUNDLE_INFO_STRING "Wayang GUI wallet")
    set(MACOSX_BUNDLE_LONG_VERSION_STRING "${VERSION_VERSION}.${VERSION_MINOR}.${VERSION_PATCH}")
    set(MACOSX_BUNDLE_BUNDLE_NAME WayangWallet)
    set(MACOSX_BUNDLE_SHORT_VERSION_STRING "${VERSION_VERSION}.${VERSION_MINOR}.${VERSION_PATCH}")
    set(MACOSX_BUNDLE_BUNDLE_VERSION "$${VERSION_VERSION}.${VERSION_MINOR}.${VERSION_PATCH}")

    find_package(Qt5PrintSupport REQUIRED)

    include_directories(/usr/include/malloc)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -maes -std=c++11 -stdlib=libc++")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -maes -D_DARWIN_C_SOURCE")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -framework Cocoa -framework OpenGL -framework CoreFoundation -framework Carbon -framework IOKit -L/usr/lib")

    set(MACOSX_BUNDLE_ICON_FILE cryptonote.icns)
    set(APPLICATION_ICON src/images/cryptonote.icns)
    set_source_files_properties(${APPLICATION_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")

    set(BUILD_PLATFORM MACOSX_BUNDLE)
    set(BUILD_RESOURCES ${APPLICATION_ICON})
	
    GET_TARGET_PROPERTY(QT_LIB_DIR "${Qt5Widgets_LIBRARIES}" LOCATION)
    GET_FILENAME_COMPONENT(QT_LIB_DIR "${QT_LIB_DIR}" PATH)
  else(APPLE)
    set(PLATFORM_DIR Linux)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -maes -std=c++11")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -maes -std=c11")
  endif (APPLE)
endif ()

include_directories(WayangCli/src/Platform/${PLATFORM_DIR})
file(GLOB PLATFORM_SOURCES WayangCli/src/Platform/${PLATFORM_DIR}/System/*)
set(CRYPTONOTE_SOURCES ${CRYPTONOTE_SOURCES} ${PLATFORM_SOURCES})

add_library(${CRYPTONOTE_LIB} STATIC ${CRYPTONOTE_SOURCES})
set_target_properties(${CRYPTONOTE_LIB} PROPERTIES COMPILE_DEFINITIONS _GNU_SOURCE)
target_link_libraries(${CRYPTONOTE_LIB} ${Boost_LIBRARIES})

add_executable(${PROJECT_NAME} ${BUILD_PLATFORM} ${BUILD_RESOURCES} ${SOURCES} ${HEADERS} ${UIS} ${RCC})
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS _GNU_SOURCE)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} ${QTMAIN} ${CRYPTONOTE_LIB} ${QRENCODE_LIB})

if (APPLE)
  qt5_use_modules(${PROJECT_NAME} PrintSupport)
elseif (UNIX)
  target_link_libraries(${PROJECT_NAME} -lpthread)
elseif (WIN32)
  target_link_libraries(${PROJECT_NAME} Imm32 Iphlpapi Winmm)
endif (APPLE)

qt5_use_modules(${PROJECT_NAME} Widgets Gui Network)

# Installation

set(CPACK_PACKAGE_NAME ${CN_PROJECT_NAME})
set(CPACK_PACKAGE_VERSION ${CN_VERSION})
set(CPACK_PACKAGE_VENDOR "Wayang Foundation")
set(CPACK_PACKAGE_CONTACT "https://nur1labs.net/")
set(CPACK_STRIP_FILES ON)
if (APPLE)
    set(CPACK_GENERATOR DragNDrop)
    install(TARGETS ${PROJECT_NAME} BUNDLE DESTINATION .)
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}.-${VERSION_RELEASE}")
elseif (UNIX)
    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
    install(FILES src/royaltieswallet.desktop DESTINATION share/applications)
    install(FILES src/images/cryptonote.png DESTINATION share/pixmaps RENAME royalties.png)
    install(FILES copyright DESTINATION share/doc/royaltieswallet)

	SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
	SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/README.md")
	SET(CPACK_PACKAGE_ICON src/images/cryptonote.png)
	
    if (NOT PACKRPM)
        set(CPACK_GENERATOR DEB)
        set(CPACK_DEBIAN_PACKAGE_NAME ${CPACK_PACKAGE_NAME})
        set(CPACK_SYSTEM_NAME amd64)
        set(CPACK_DEBIAN_PACKAGE_MAINTAINER "${CPACK_PACKAGE_VENDOR} <xrydev@gmail.com>")
        set(CPACK_DEBIAN_PACKAGE_SECTION Office)
        set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
        set(CPACK_DEBIAN_PACKAGE_DESCRIPTION "Wayang WYG wallet
 Wayang is a decentrilized privacy protected peer-to-peer
 cryptocurrency and untraceable encrypted messaging system. Wayang is
 open-source; its design is public, nobody owns or controls Wayang and
 everyone can take part. Wayang is Smart, Fast And Easy Used.
 .
 Features of the Royalties wallet listed bellow:
 * Classic Bitcoin alike appearance in WayangCli based cryptocurrency,
   made with QT and open-source.
 * Instant anonymous XRY transfers and transfers notifications
 * Instant untraceable encrypted messages transfers and notifications
 * Safe and secure, full Royalties network node in wallet, fast network
   syncronization.
 * Wallet encryption
 * Fast and hardware optimized
 * Open and easy. Private keys can be exported into other clients
 * Decreasing overload ico.")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_DEBIAN_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${VERSION_RELEASE}.${CPACK_SYSTEM_NAME}")
	else ()
        set(CPACK_GENERATOR RPM)
        set(CPACK_SYSTEM_NAME x86_64)
        set(CPACK_RPM_PACKAGE_RELEASE ${VERSION_RELEASE})
        set(CPACK_RPM_PACKAGE_LICENSE "GPL3")
        set(CPACK_RPM_PACKAGE_GROUP Office)
        set(CPACK_RPM_PACKAGE_REQUIRES "qt5-qtbase >= 5.3.2, qt5-qtbase-gui >= 5.3.2")
        set(CPACK_RPM_PACKAGE_SUMMARY "Royalties wallet")
        set(CPACK_RPM_PACKAGE_DESCRIPTION "Open-source Royalties GUI wallet
 Royalties is a decentrilized privacy protected peer-to-peer
 cryptocurrency and untraceable encrypted messaging system. Royalties is
 open-source; its design is public, nobody owns or controls Royalties and
 everyone can take part.

 Features of the Royalties wallet listed bellow:
 *Classic Bitcoin alike appearance in WayangCli based cryptocurrency,
    made with QT and open-source.
 *Instant anonymous Royalties transfers and transfers notifications
 *Instant untraceable encrypted messages transfers and notifications
 *Safe and secure, full Royalties network node in wallet, fast network
    syncronization.
 *Wallet encryption
 *Fast and hardware optimized
 *Open and easy. Private keys can be exported into other clients
 *Decreasing overload ico.")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${VERSION_RELEASE}.${CPACK_SYSTEM_NAME}")
    endif ()
elseif (WIN32)
  install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)
  set(CPACK_GENERATOR ZIP)
endif (APPLE)

include(CPack)
