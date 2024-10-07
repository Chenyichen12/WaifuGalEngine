import QtQuick
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
            if (textBar.showing) {
                textBar.skip();
                return;
            } 
            if(stage.transforming){
                stage.skip();
                return;
            }
            game.moveNext();
        }
    }
}
