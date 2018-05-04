#include "GraphColoring.h"

void ColoringGraph(Graph *graph)
{
	#if 0
	if (TwoColor(graph) == 0) {
		PrintInfoGraph(graph);

		GraphImageCreation(graph);
		system("dot -Tpng graph.gv -ograph.png");
	}

	RebootGraph(graph);
	#endif

	#if 0
	if (Coloring(graph, 6) == 0) {
		PrintInfoGraph(graph);

		GraphImageCreation(graph);
		system("dot -Tpng graph.gv -ograph.png");
	}

	RebootGraph(graph);
	#endif

	#if 1
	int act;

	system("clear");

	while (act != 7) {
		printf("\n");
		printf("1) Расскарасить граф в 2 цвета\n");
		printf("2) Расскарасить граф в 3 или менее цвета\n");
		printf("3) Расскарасить граф в 4 или менее цвета\n");
		printf("4) Расскарасить граф в 5 или менее цветов\n");
		printf("5) Расскарасить граф\n");
		printf("6) Вывод информации о црафе\n");
		printf("7) Выход\n");
		printf("Выберите действие: ");
		scanf("%d", &act);

		switch(act) {
			case 1:
				system("clear");
				RebootGraph(graph);
				if (TwoColor(graph) == 0) {
					GraphImageCreation(graph);
					system("dot -Tpng graph.gv -ograph.png");
				}
				break;
			case 2:
				system("clear");
				RebootGraph(graph);
				if (TFFColor(graph, 3) == 0) {
					GraphImageCreation(graph);
					system("dot -Tpng graph.gv -ograph.png");
				}
				break;
			case 3:
				system("clear");
				RebootGraph(graph);
				if (TFFColor(graph, 4) == 0) {
					GraphImageCreation(graph);
					system("dot -Tpng graph.gv -ograph.png");
				}
				break;
			case 4:
				system("clear");
				RebootGraph(graph);
				if (TFFColor(graph, 5) == 0) {
					GraphImageCreation(graph);
					system("dot -Tpng graph.gv -ograph.png");
				}
				break;
			case 5:
				system("clear");
				RebootGraph(graph);
				if (NColor(graph) == 0) {
					GraphImageCreation(graph);
					system("dot -Tpng graph.gv -ograph.png");
				}
				break;
			case 6:
				system("clear");
				PrintInfoGraph(graph);
				break;
			case 7:
				break;
			default:
				system("clear");
				printf("Ошибка действия\n\n");
		}
	}
	#endif
}

int TwoColor(Graph *graph)
{
	Node *node = graph->Head;

	node->color = 0;

	if (TwoColorRun(node) == 1) {
		printf("Error, 2 color\n");
		return 1;
	}

	return 0;
}

int TwoColorRun(Node *node)
{
	if (node->status == 1)
		return 0;

	int nextColor;
	if (node->color == 0) {
		nextColor = 1;
	} else if (node->color == 1) {
		nextColor = 0;
	}

	HashT *contact = node->Contact;
	for (int i = 0; i < node->number; i++) {
		int act = TwoColorCheckNode(contact->node, node->color);
		if (act == 1) {
			return 1;
		} else if (act == 0) {
			contact->node->color = nextColor;
		}
		
		contact = contact->next;
	}

	node->status = 1;

	contact = node->Contact;
	for (int i = 0; i < node->number; i++) {
		if (TwoColorRun(contact->node) == 1)
			return 1;
		contact = contact->next;
	}

	return 0;
}

int TwoColorCheckNode(Node *node, int color)
{
	if (node->color == color)
		return 1;

	if (node->color != -1)
		return 2;

	return 0;
}

int TFFColor(Graph *graph, int color)
{
	int act = TFFColorCheckPow(graph, color);
	if (act == 1)
		return 1;

	return 0;
}

int TFFColorCheckPow(Graph *graph, int pow)
{
	Node *node = graph->Head;

	if (node->next == NULL) {
		node->status = 1;
		node->color = 0;
		return 0;
	}

	for (int i = 0; i < graph->number; i++) {
		if (node->number < pow && node->status != 1) {
			graph = DeleteNodeSave(graph, node);

			TFFColorCheckPow(graph, pow);

			graph = RestoringNode(graph, node);

			int act = TFFColorRun(node, pow);
			if (act == 1)
				return 1;
		}

		node = node->next;
	}

	return 0;
}

int TFFColorRun(Node *node, int numColor)
{
	if (node->status == 1)
		return 0;

	int act = TFFColorCheckNode(node, numColor, 0);
	if (act == 1)
		return 1;

	return 0;
}

int TFFColorCheckNode(Node *node, int numColor, int color)
{
	if (node->status == 1)
		return 0;

	HashT *NCont = node->Contact;

	for (int i = 0; i < node->number && node->color == -1; i++) {
		if (NCont->node->color == color) {
			int act = TFFColorCheckNode(node, numColor, color + 1);
			if (act == 1)
				return 1;
		}
		NCont = NCont->next;
	}

	if (numColor < color) {
		printf("Not available color");
		return 1;
	}

	if (node->color == -1) {
		node->color = color;
		node->status = 1;
	}

	return 0;
}

int NColor(Graph *graph)
{
	Node *node = graph->Head;

	NColorRun(node);

	return 0;
}

int NColorRun(Node *node)
{
	int color = 0;

	color = NColorCheck(node, color);

	return 0;
}

int NColorCheck(Node *node, int color)
{
	HashT *contact = node->Contact;
	for (int i = 0; i < node->number; i++) {
		if (color == contact->node->color)
			// NColorCheck

		contact = contact->next;
	}
	return 0;
}

// int NColor