const pages = require('./manifest.json')

module.exports = {
	'title': 'C Programming Notes',
//	theme: 'dark',
	themeConfig: {
		smoothScroll: true,
		sidebar: [
			{
				title: 'Main Pages',
				children: pages
			}
		]
	}
}
