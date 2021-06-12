# QuickVSG

This is a basic demo for integrating the framework [VulkanSceneGraph](https://github.com/vsg-dev/VulkanSceneGraph) to QtQuick. 

Features:
1. Provide a standard QQuickItem-based control, called `Canvas`, rendered by VSG and can be integrated seamlessly into QtQuick app;
2. Support mouse interaction, key events and resizing;
3. Support dynamically load VSG models. 

The core idea is sharing a VkImage between VSG and QSG(short for Qt SceneGraph) via Vulkan's external memory extension.

The idea is possible because:

1. VSG can create a framebuffer for offline rendering. Specifically, the color image attachment in the framebuffer is created with `VkExportMemoryAllocateInfo` enabled, which makes the image sharable between different Vulkan devices via external memory extension;
2. Qt has adopted a new rendering layer called Rhi, which fully supports Vulkan-based QtQuick rendering. So when QtQuick is running on Vulkan, it is possible to render a customized VkImage on top of the QSG using `QSGSimpleTextureNode`;
3. By creating the `QSGSimpleTextureNode` using the VkImage imported from VSG via `VkImportMemoryWin32HandleInfoKHR`(on Win32) or `VkImportMemoryFdInfoKHR`(on Unix), the texture rendered by VSG can shown on the QtQuick window.

This demo is built & tested with:
1. Qt 6.1.1;
2. VSG 0.1.3;
3. Vulkan SDK 1.2.176.1;
4. on a Windows netbook with a integrated GPU (Intel HD Graphics 615) which supports Vulkan 1.0.0.

Although the codes in the demo try to adapt itself to Unix environment, it is not tested under that platform yet.

The following repos/examples are referenced in the demo:
1. [vsgheadless](https://github.com/vsg-dev/vsgExamples/tree/master/examples/viewer/vsgheadless);
2. [vsgrendertotexture](https://github.com/vsg-dev/vsgExamples/tree/master/examples/viewer/vsgrendertotexture);
3. [Qt vulkantextureimport](https://doc.qt.io/qt-6/qtquick-scenegraph-vulkantextureimport-example.html);
4. [vsgQtViewer](https://github.com/anormann1974/vsgQtViewer). The class `KeyboardMap` is taken from this repo. Thanks.