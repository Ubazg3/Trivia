#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory) {}



RequestResult LoginRequestHandler::handleRequest(RequestInfo& request)
{
	RequestResult result;

	if (request.id == LOGIN_CODE)
	{
		// Deserialize login request
		LoginRequest loginReq = JsonRequestPacketDeserializer::deserializeLoginRequest(request.buffer);
		std::cout << "Login attempt by user: " << loginReq.username << std::endl;
		return login(request);
	}
	else if (request.id == SIGNUP_CODE)
	{
		// Deserialize signup request
		SignupRequest signupReq = JsonRequestPacketDeserializer::deserializeSignupRequest(request.buffer);
		std::cout << "Signup attempt by user: " << signupReq.username << std::endl;
		return signup(request);
	}
	else {
		// Shouldn�t happen if isRequestRelevant was checked first
		ErrorResponse err{ "Unknown request code." };
		return RequestResult{
			JsonResponsePacketSerializer::serializeResponse(err),
			this
		};
	}
}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& request)
{
	return request.id == LOGIN_CODE || request.id == SIGNUP_CODE;
}

RequestResult LoginRequestHandler::login(const RequestInfo& request)
{
	LoginRequest log;
	LoginStatus status;
	RequestResult res;
	log = JsonRequestPacketDeserializer::deserializeLoginRequest(request.buffer);
	std::string username = log.username;
	std::string password = log.password;
	status = this->m_handlerFactory.getLoginManager().login(username, password);
	if (status == LoginStatus::Success)
	{
		LoginResponse response{ LOGIN_RESPONSE };
		res.response = JsonResponsePacketSerializer::serializeResponse(response);
		res.newHandler = this->m_handlerFactory.createMenuRequestHandler(username);
	}
	else
	{
		std::string errCode;
		if(status == LoginStatus::UserNotExist) errCode = "UserNotExist";
		else if(status == LoginStatus::WrongPassword) errCode = "WrongPassword"; 
		else if(status == LoginStatus::AlreadyLoggedIn) errCode = "AlreadyLoggedIn"; 
		else if(status == LoginStatus::DbError) errCode = "DbError";
		else { errCode = "login error"; }
		ErrorResponse error{ errCode };
		res.response = JsonResponsePacketSerializer::serializeResponse(error);
		res.newHandler = new LoginRequestHandler(this->m_handlerFactory);
	}
	return res;
}

RequestResult LoginRequestHandler::signup(const RequestInfo& request)
{
	SignupRequest log;
	SignUpStatus status;
	RequestResult res;
	log = JsonRequestPacketDeserializer::deserializeSignupRequest(request.buffer);
	std::string username = log.username;
	std::string password = log.password;
	std::string email = log.email; // Add email to
	status = this->m_handlerFactory.getLoginManager().signup(username, password, email);
	if (status == SignUpStatus::Success)
	{
		LoginResponse response{ SIGNUP_RESPONSE };
		res.response = JsonResponsePacketSerializer::serializeResponse(response);
		res.newHandler = this->m_handlerFactory.createMenuRequestHandler(username);
	}
	else
	{
		std::string errCode;
		if (status == SignUpStatus::UserAlreadyExists) errCode = "UserAlreadyExists";
		else if(status == SignUpStatus::DbError) errCode = "DbErrors";
		else { errCode = "Signup error"; }
		ErrorResponse error{ errCode };
		res.response = JsonResponsePacketSerializer::serializeResponse(error);
		res.newHandler = new LoginRequestHandler(this->m_handlerFactory);
	}
	return res;
}