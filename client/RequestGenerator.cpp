#include "RequestGenerator.h"
#include "DatabaseObject.h"
#include "Project.h"
#include "ObjectsContainer.h"

RequestGenerator::RequestGenerator(void)
{
	socket_id = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_id == INVALID_SOCKET)
	{
		int error = WSAGetLastError();
		mainForm->MessageBox(L"�� ������� ������� �����.");
	}
}

int RequestGenerator::connectToServer(char *address, int port)
{
	memset(&server_address, 0, sizeof(struct sockaddr_in));
	server_address.sin_family = AF_INET; //IPv4
	server_address.sin_port = htons(port);
	server_address.sin_addr.s_addr = inet_addr(address);

	int returned = connect(socket_id, (const sockaddr*)&server_address, sizeof(struct sockaddr_in));
	if (returned != 0)
	{
		mainForm->MessageBox(L"�� ������� ������������.");
	}

	return returned;
}

RequestGenerator::~RequestGenerator(void)
{
}

RequestGenerator* RequestGenerator::_instance = 0;

RequestGenerator* RequestGenerator::instance()
{
	if (_instance == 0)
	{
		_instance = new RequestGenerator();
	}
	return _instance;
}

ResponseBody RequestGenerator::sendRequest(char method[4], char URI[50], char* body, int bodySize)
{
	RequestHeader *header = new RequestHeader; //��������� �������

	strcpy(header->method, method);
	strcpy(header->URI, URI);
	header->bodySize = bodySize;

	send(socket_id, (char*)header, sizeof(RequestHeader), NULL);
	send(socket_id, body, bodySize, NULL);

	//��� �������� ������ ��������� ������

	ResponseHeader *response = new ResponseHeader;
	recv(socket_id, (char*)response, sizeof(RequestHeader), NULL); //�������� ��������� ������

	char *responseBody = (char*)malloc(response->bodySize);
	recv(socket_id, (char*)responseBody, response->bodySize, NULL);

	ResponseBody resp;
	if (strcpy(response->status, "OK"))
	{
		resp.body = responseBody;
		resp.size = response->bodySize;

		return resp;
	} else if (strcpy(response->status, "FAIL")) //���� ��������� ������
	{
		WCHAR *messageEncoded = (WCHAR*)calloc(response->bodySize, sizeof(WCHAR));
		mbstowcs(messageEncoded, responseBody, response->bodySize);
		mainForm->showError(messageEncoded); //��������� ��������� �� ����
		
		resp.size = 0;
		return resp; //��������� � ��������
	} else {
		mainForm->showError(L"���������� ����� �������.");
		
		resp.size = 0;
		return resp;
	}
}

void RequestGenerator::groupProjects(LPCWSTR groupName)
{
	ResponseBody result = sendRequest("GET", "/project/group", (char*)groupName, sizeof(groupName));

	if (result.size != 0)
	{
		ObjectsContainer *objects = new ObjectsContainer(new Project(), result.size);
		objects->setDataPointer(result.body);

		mainForm->displayProjects(objects);
	}
}

void RequestGenerator::lecturerProjects(LPCWSTR lenctuerName)
{
	ResponseBody result = sendRequest("GET", "/project/lecturer", (char*)lenctuerName, sizeof(lenctuerName));

	if (result.size != 0)
	{
		ObjectsContainer *objects = new ObjectsContainer(new Project(), result.size);
		objects->setDataPointer(result.body);

		mainForm->displayProjects(objects);
	}
}

void RequestGenerator::allProjects()
{
	ResponseBody result = sendRequest("GET", "/project", NULL, 0);

	if (result.size != 0)
	{
		ObjectsContainer *objects = new ObjectsContainer(new Project(), result.size);
		objects->setDataPointer(result.body);

		mainForm->displayProjects(objects);
	}
}

void RequestGenerator::addProject(LPCWSTR task, LPCWSTR subject, LPCWSTR dueTo, int completeness, LPCWSTR lecturer, LPCWSTR student)
{
	Project *newOne = new Project(); //����������� � ���� ��������

	wcscpy(newOne->task, task);
	wcscpy(newOne->subject, subject);
	wcscpy(newOne->dueTo, dueTo);
	newOne->completeness = completeness;
	wcscpy(newOne->lecturer, lecturer);

	sendRequest("POST", "/project", (char*)newOne, sizeof(Project));
}

void RequestGenerator::addLecturer(LPCWSTR fullName)
{

}

void RequestGenerator::addStudent(LPCWSTR fullName, LPCWSTR group)
{

}

void RequestGenerator::editProject(LPCWSTR task, LPCWSTR subject, LPCWSTR dueTo, int completeness, LPCWSTR lecturer, LPCWSTR student)
{
	Project *newOne = new Project();

	wcscpy(newOne->task, task);
	wcscpy(newOne->subject, subject);
	wcscpy(newOne->dueTo, dueTo);
	newOne->completeness = completeness;
	wcscpy(newOne->lecturer, lecturer);

	sendRequest("PUT", "/project", (char*)newOne, sizeof(Project));
}

void RequestGenerator::removeProject(int id)
{
	sendRequest("DELETE", "/project", (char*)id, sizeof(int));
}

