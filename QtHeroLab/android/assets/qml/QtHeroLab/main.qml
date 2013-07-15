import QtQuick 2.0
import HeroLab 1.0

Image
{
    width: 360
    height: 360
	fillMode: Image.Tile
	source: "mainwindow.bmp"

	MouseArea
	{
        anchors.fill: parent
		onClicked: Qt.quit();
    }

	FileLister
	{
		id: path
	}
	Portfolio
	{
		Component.onCompleted:
		{
			var list = path.list();
			for(var i = 0; i < list.length; i++)
				console.debug(list[i]);
		}

		id: por
		file : "Sonitri the Star Queen.por"
	}

	Rectangle
	{
		width: 180
		height: 50
		color: "#80333fa6"
		radius: 15
		border.width: 2
		border.color: "black"
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		Text
		{
			text: qsTr("Hello World")
			anchors.fill: parent
			verticalAlignment: Text.AlignVCenter
			horizontalAlignment: Text.AlignHCenter
			font.pointSize: 20
		}
	}
}
