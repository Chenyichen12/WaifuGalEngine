import QtQuick
import QtQuick.Layouts

Item {
    width: 1000
    height: 600

    Repeater {
        id: characterScene
        anchors.fill: parent
        model: stage.showCharacters
        delegate: Item {
            anchors.fill: parent
            Image {
                source: modelData.url
                opacity: modelData.opacity
                fillMode: Image.PreserveAspectFit
                height: characterScene.height
                x: modelData.location.x * characterScene.width - this.width / 2
                y: modelData.location.y * characterScene.height
            }
        }
    }
    Rectangle {
        color: "#80000000"
        anchors.bottom: parent.bottom
        width: parent.width
        height: parent.height * 0.3
        Text {
            anchors.fill: parent
            anchors.leftMargin: 80
            anchors.rightMargin: 80
            anchors.topMargin: 40
            color: "white"
            text: textBar.showText
            font.pixelSize: 20
        }
        Rectangle {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.topMargin: -25
            anchors.leftMargin: 20
            radius: 10
            width: textBar.sayingName == "" ? 0 : nameBar.width + 20
            height: 50
            color: "black"
            Text {
                id: nameBar
                anchors.centerIn: parent
                color: "white"
                text: textBar.sayingName
                font.pixelSize: 20
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            if (choiceBar.visible) {
                return;
            }
            if (textBar.showing) {
                textBar.skip();
                return;
            }
            if (stage.transforming) {
                stage.skip();
                return;
            }
            game.moveNext();
        }
    }

    Rectangle {
        id: choiceBar
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width * 0.8
        height: parent.height * 0.7
        visible: choiceView.visible
        color: "transparent"
        ColumnLayout {
            anchors.fill: parent
            Layout.fillHeight: true
            Repeater {
                model: choiceView.choices
                Rectangle {
                    id: choiceBox
                    radius: 10
                    Layout.alignment: Qt.AlignCenter
                    height: 50
                    width: choiceBar.width
                    color: "black"
                    Text {
                        anchors.centerIn: parent
                        text: modelData
                        color: "white"
                        font.pixelSize: 20
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            choiceView.choose(index);
                        }
                        onEntered: {
                            choiceBox.color = "red";
                        }
                        onExited: {
                            choiceBox.color = "black";
                        }
                    }
                }
            }
        }
    }
}
