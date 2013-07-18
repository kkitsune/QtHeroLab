import QtQuick 2.0
import HeroLab 1.0

Image
{
	width: 800
	height: 600
	fillMode: Image.Tile
	source: "mainwindow.bmp"

	Portfolio
	{
		property QtObject path : FileLister { }
		property var dir

		Component.onCompleted:
		{
			dir = path.list();
			fillList();
		}

		function fillList()
		{
			if(path.level > 0)
				porList.model.append({"name": "../"});
			for(var i = 0; i < dir.length; i++)
				porList.model.append({"name": dir[i]});
		}

		function onFileSelected(index)
		{
			var t = porList.model.get(index).name;
			if(t[t.length - 1] === "/")
			{
				if(t === "../")
				{
					path.upOne();
					dir = path.list();
				}
				else
					dir = path.list(t);
				porList.model.clear();
				fillList();
			}
			else
			{
				file = t;
				charList.view.model.clear();
				for(var i = 0; i < characterList.length; i++)
					charList.view.model.append({"name": characterList[i]});
				charList.visible = true;
				charList.enabled = true;
				porList.visible = false;
				porList.enabled = false;
			}
		}

		id: por
	}

	PortfolioList
	{
		id: porList
		onItemClicked: por.onFileSelected(index)
	}

	CharacterList
	{
		id: charList
		visible: false
		enabled: false
		onCharSelected:
		{
			block.text = por.getCharacter(name);
			visible = false;
			enabled = false;
			block.visible = true;
			block.enabled = true;
		}
		onBack:
		{
			view.model.clear();
			visible = false;
			enabled = false;
			porList.visible = true;
			porList.enabled = true;
		}
	}

	StatBlock
	{
		id: block
		visible: false
		enabled: false
		onBack:
		{
			visible = false;
			enabled = false;
			charList.visible = true;
			charList.enabled = true;
		}
	}
}
