import QtQuick 2.0
import HeroLab 1.0

Rectangle
{
    width: 360
    height: 360
	Text
	{
        text: qsTr("Hello World")
        anchors.centerIn: parent
    }
	MouseArea
	{
        anchors.fill: parent
		onClicked: Qt.quit();
    }

	Portfolio
	{
		id: por
		file : "Sonitri the Star Queen.por"
	}
}
