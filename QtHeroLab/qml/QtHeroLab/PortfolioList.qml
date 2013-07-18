import QtQuick 2.0

ListView
{
	id: view
	signal itemClicked(var index)

	clip: true
	anchors.rightMargin: 25
	anchors.leftMargin: 25
	anchors.bottomMargin: 25
	anchors.topMargin: 25
	anchors.fill: parent
	model: ListModel { }
	delegate: Item
	{
		height: row.height + 5
		Row
		{
			id: row
			spacing: 5
			CustomListElement
			{
				text: name
				anchors.verticalCenter: parent.verticalCenter
				onClicked: view.itemClicked(index)
			}
		}
	}
}
