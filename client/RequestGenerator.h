#pragma once
#include <stdlib.h>
#include <string>
#include <windows.h>

#include "..\ProtocolSpecification.h"

class RequestGenerator
{
public:
	~RequestGenerator(void);

	static RequestGenerator* instance();

	void sendRequest(char method[4], char URI[50], char* body, int bodySize);

	void groupProjects(LPCWSTR groupName);
	void lecturerProjects(LPCWSTR lenctuerName);
	void allProjects();
	void addProject(LPCWSTR task, LPCWSTR subject, LPCWSTR dueTo, int completeness, LPCWSTR lecturer, LPCWSTR student);
	void addLecturer(LPCWSTR fullName);
	void addStudent(LPCWSTR fullName, LPCWSTR group);
	void editProject(LPCWSTR task, LPCWSTR subject, LPCWSTR dueTo, int completeness, LPCWSTR lecturer, LPCWSTR student);
	void removeProject(int id);
protected:
	RequestGenerator(void);
private:
	static RequestGenerator* _instance;
};
