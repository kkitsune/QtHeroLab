import QtQuick 2.0

Rectangle
{
	property alias text: label.text
	signal clicked

	width: label.width + 10
	height: label.height + 10
	color: "#800d8fa0"
	radius: 7
	border.color: "black"
	Text
	{
		Component.onCompleted: if(platform.isAndroid) font.pixelSize *= 2
		x: 5
		y: 5
		id: label
		font.pixelSize: 20
	}
	MouseArea
	{
		anchors.fill: parent
		hoverEnabled: true
		onEntered: parent.color = "#c87ddfe6"
		onExited: parent.color = "#800d8fa0"
		onClicked: parent.clicked()
	}
}
