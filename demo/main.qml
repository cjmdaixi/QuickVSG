import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.1
import Qt.labs.platform 1.1
import QuickVSG 1.0 as QV

ApplicationWindow {
    id: rootWindow
    visible: true;
    title: qsTr("VSG pid:") + $pid
    
    width: 800
    height: 600

    QV.Canvas {
        id: canvas
        anchors.fill: parent
    }

    Rectangle{
        anchors{
            right: parent.right
            top: parent.top
            bottom:parent.bottom
            margins:10
        }
        width: 150

        border{
            width: 2
            color: "black"
        }
        radius: 5
        ColumnLayout{
            id: buttonLayout
            anchors{
                fill: parent
                margins: 20
            }

            Button{
                text:"Load"
                onClicked:{
                    fileDialog.open();
                }
                Layout.fillWidth: true
            }
            Item{
                Layout.fillHeight: true
            }
        }
    }
    Popup{
        id: warningPopup
        width: 300
        height: 150
        modal: true
        x: parent.width / 2 - width / 2
        y: parent.height / 2 - height / 2

        closePolicy: Popup.NoAutoClose

        function show(msg){
            msgLabel.text = msg;
            warningPopup.open();
        }

        Label{
            id: msgLabel
            anchors{
                centerIn: parent
                verticalCenterOffset: -20
            }
            font{
                family: "Arial"
                pointSize: 10
            }
            wrapMode: Text.WordWrap
            color: "black"
        }
        Button{
            anchors{
                bottom: parent.bottom; bottomMargin: 10
                horizontalCenter: parent.horizontalCenter
            }
            text: qsTr("OK")
            onClicked: {
                warningPopup.close();
            }
        }
    }
    
    FileDialog {
        id: fileDialog
        title: "Please choose a VSG model file"
        folder: $modelsPath
        nameFilters: [ "VSG files (*.vsgt *.vsgb)"]
        onAccepted: {
            var path = fileDialog.file.toString();
            path= path.replace(/^(file:\/{3})|(qrc:\/{2})|(http:\/{2})/,"");
            var cleanPath = decodeURIComponent(path);
            canvas.modelPath = cleanPath;
        }
        onRejected: {

        }
    }
}
