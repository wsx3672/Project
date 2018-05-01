//Visitor.h

#ifndef _VISITOR_H
#define _VISITOR_H

typedef signed long int Long;

#include <afxwin.h>
//MainForm Control Class
class Diagram;
class Class;
class MemoBox;
class Selection;
//Entity Class
class Template;
class ClassName;
class Method;
class Attribute;
class Selection;
class Reception;
class Line;
//Entity Class
class Generalization;
class Realization;
class Dependency;
class Association;
class DirectedAssociation;
class Aggregation;
class Aggregations;
class Composition;
class Compositions;
class MemoLine;
class SelfGeneralization;
class SelfDependency;
class SelfAggregation;
class SelfAssociation;
class SelfAggregations;
class SelfDirectedAssociation;
class SelfComposition;
class SelfCompositions;
//SubForm Control Class
class Text;
class Relation;
class SelfRelation;
class Visitor{
public:
	virtual ~Visitor();
	//Composite
	virtual void Visit(Diagram *diagram, Selection *selection, Long distanceX, Long distanceY) = 0;
	virtual void Visit(Class *object, CDC* pDC) = 0;
	virtual void Visit(MemoBox* memobox, CDC *pDC) = 0;
	virtual void Visit(Selection *selection, CDC *pDC) = 0;
	//Component
	virtual void Visit(Template *object, CDC *pDC) = 0;
	virtual void Visit(ClassName *className, CDC *pDC) = 0;
	virtual void Visit(Method *method, CDC *pDC) = 0;
	virtual void Visit(Attribute *attribute, CDC *pDC) = 0;
	virtual void Visit(Reception* reception, CDC* pDC) = 0;
	virtual void Visit(Line *line, CDC* pDC) = 0;
	//RelationLines
	virtual void Visit(SelfRelation *selfRelation, CDC *cPaintDc) = 0;
	virtual void Visit(Relation *relation, CDC *cPaintDc) = 0;
	virtual void Visit(Generalization *generalization, CDC* pDC) = 0;		//�Ϲ�ȭ
	virtual void Visit(Realization * realization, CDC* pDC) = 0;		//��üȭ
	virtual void Visit(Dependency *dependency, CDC* pDC) = 0;			//����
	virtual void Visit(Association *association, CDC* pDC) = 0;		//����ȭ 
	virtual void Visit(DirectedAssociation *directedAssociation, CDC* pDC) = 0;		//��������
	virtual void Visit(Aggregation *aggregation, CDC* pDC) = 0;		//����
	virtual void Visit(Aggregations *aggregations, CDC* pDC) = 0;		//���տ���
	virtual void Visit(Composition *composition, CDC* pDC) = 0;		//�ռ�
	virtual void Visit(Compositions *compositions, CDC* pDC) = 0;		//���տ���
	virtual void Visit(MemoLine* memobox, CDC *pDC) = 0;				//�޸�
	virtual void Visit(SelfGeneralization *selfGeneralization, CDC *pDC) = 0;
	virtual void Visit(SelfDependency *selfDependency, CDC *pDC) = 0;
	virtual void Visit(SelfAggregation *selfAggregation, CDC *pDC) = 0;
	virtual void Visit(SelfAssociation *selfAssociation, CDC *pDC) = 0;
	virtual void Visit(SelfAggregations *selfAggregations, CDC *pDC) = 0;
	virtual void Visit(SelfDirectedAssociation *selfDirectedAssociation, CDC *pDC) = 0;
	virtual void Visit(SelfComposition *selfComposition, CDC *pDC) = 0;
	virtual void Visit(SelfCompositions *selfCompositions, CDC *pDC) = 0;

	virtual void Visit(Class *object, Long distanceX, Long distanceY) = 0;
	virtual void Visit(MemoBox *memoBox, Long distanceX, Long distanceY) = 0;
	virtual void Visit(Text* text, CDC *pDC) = 0;

	//�������� �ؽ�Ʈ
protected:
	Visitor();
};

#endif // _VISITOR_H
