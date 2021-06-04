#pragma once
#include"Set.h"

bool TestAdd()
{
	Set<int> set;
	int a = 5;
	set.Add(a);
	set.UpdateRound();
	return *set.begin() == a;
}

bool TestHas()
{
	Set<int> set;
	int a = 5;
	set.Add(a);
	return set.Has(a);
}

bool TestDelete()
{
	Set<int> set;
	int a = 5;
	set.Add(a);
	set.Delete(a);
	return !set.Has(a);
}

bool TestUnion()
{
	Set<int> result_set;
	result_set.Add(1);
	result_set.Add(2);
	result_set.Add(3);
	Set<int> set1;
	Set<int> set2;
	set1.Add(1);
	set1.Add(2);
	set2.Add(2);
	set2.Add(3);
	Set<int> set3 = Union(set1, set2);
	set3.UpdateRound();
	for (auto el : set3)
		if (!result_set.Has(el))
			return false;
	return true;
}

bool TestIntersection()
{
	Set<int> result_set;
	result_set.Add(2);
	Set<int> set1;
	Set<int> set2;
	set1.Add(1);
	set1.Add(2);
	set2.Add(2);
	set2.Add(3);
	Set<int> set3 = Intersection(set1, set2);
	set3.UpdateRound();
	for (auto el : set3)
		if (!result_set.Has(el))
			return false;
	return true;
}

bool TestRelativeComplement()
{
	Set<int> result_set;
	result_set.Add(1);
	Set<int> set1;
	Set<int> set2;
	set1.Add(1);
	set1.Add(2);
	set2.Add(2);
	set2.Add(3);
	Set<int> set3 = RelativeComplement(set1, set2);
	set3.UpdateRound();
	for (auto el : set3)
		if (!result_set.Has(el))
			return false;
	return true;
}
