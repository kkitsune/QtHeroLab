import QtQuick 2.0

Image
{
	property alias text: blockContent.text
	signal back

	fillMode: Image.Tile
	source: "background.bmp"

	anchors.rightMargin: 25
	anchors.leftMargin: 25
	anchors.bottomMargin: 25
	anchors.topMargin: 25
	anchors.fill: parent

	Flickable
	{
		anchors.topMargin: backBtn.height
		anchors.fill: parent
		contentWidth: blockContent.width
		contentHeight: blockContent.height
		clip: true

		TextEdit
		{
			id: blockContent
			readOnly: true
		}
	}

	MouseArea
	{
		anchors.top: parent.top
		anchors.left: parent.left
		height: backBtn.height
		width: 100

		hoverEnabled: true
		onEntered: backBtn.color = "darkgray"
		onExited: backBtn.color = "black"

		onClicked: parent.back()

		Text
		{
			id: backBtn
			Component.onCompleted: if(platform.isAndroid) font.pixelSize *= 2
			text: "<- Back"
			font.pixelSize: 15
			color: "black"
			font.bold: true
		}
	}
}
