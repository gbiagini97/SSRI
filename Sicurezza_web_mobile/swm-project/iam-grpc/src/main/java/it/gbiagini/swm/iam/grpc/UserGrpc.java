package it.gbiagini.swm.iam.grpc;

import static io.grpc.MethodDescriptor.generateFullMethodName;
import static io.grpc.stub.ClientCalls.asyncBidiStreamingCall;
import static io.grpc.stub.ClientCalls.asyncClientStreamingCall;
import static io.grpc.stub.ClientCalls.asyncServerStreamingCall;
import static io.grpc.stub.ClientCalls.asyncUnaryCall;
import static io.grpc.stub.ClientCalls.blockingServerStreamingCall;
import static io.grpc.stub.ClientCalls.blockingUnaryCall;
import static io.grpc.stub.ClientCalls.futureUnaryCall;
import static io.grpc.stub.ServerCalls.asyncBidiStreamingCall;
import static io.grpc.stub.ServerCalls.asyncClientStreamingCall;
import static io.grpc.stub.ServerCalls.asyncServerStreamingCall;
import static io.grpc.stub.ServerCalls.asyncUnaryCall;
import static io.grpc.stub.ServerCalls.asyncUnimplementedStreamingCall;
import static io.grpc.stub.ServerCalls.asyncUnimplementedUnaryCall;

/**
 */
@javax.annotation.Generated(
    value = "by gRPC proto compiler (version 1.28.1)",
    comments = "Source: user.proto")
public final class UserGrpc {

  private UserGrpc() {}

  public static final String SERVICE_NAME = "User";

  // Static method descriptors that strictly reflect the proto.
  private static volatile io.grpc.MethodDescriptor<it.gbiagini.swm.iam.grpc.UserOuterClass.Credentials,
      it.gbiagini.swm.iam.grpc.UserOuterClass.Response> getRegisterUserMethod;

  @io.grpc.stub.annotations.RpcMethod(
      fullMethodName = SERVICE_NAME + '/' + "registerUser",
      requestType = it.gbiagini.swm.iam.grpc.UserOuterClass.Credentials.class,
      responseType = it.gbiagini.swm.iam.grpc.UserOuterClass.Response.class,
      methodType = io.grpc.MethodDescriptor.MethodType.UNARY)
  public static io.grpc.MethodDescriptor<it.gbiagini.swm.iam.grpc.UserOuterClass.Credentials,
      it.gbiagini.swm.iam.grpc.UserOuterClass.Response> getRegisterUserMethod() {
    io.grpc.MethodDescriptor<it.gbiagini.swm.iam.grpc.UserOuterClass.Credentials, it.gbiagini.swm.iam.grpc.UserOuterClass.Response> getRegisterUserMethod;
    if ((getRegisterUserMethod = UserGrpc.getRegisterUserMethod) == null) {
      synchronized (UserGrpc.class) {
        if ((getRegisterUserMethod = UserGrpc.getRegisterUserMethod) == null) {
          UserGrpc.getRegisterUserMethod = getRegisterUserMethod =
              io.grpc.MethodDescriptor.<it.gbiagini.swm.iam.grpc.UserOuterClass.Credentials, it.gbiagini.swm.iam.grpc.UserOuterClass.Response>newBuilder()
              .setType(io.grpc.MethodDescriptor.MethodType.UNARY)
              .setFullMethodName(generateFullMethodName(SERVICE_NAME, "registerUser"))
              .setSampledToLocalTracing(true)
              .setRequestMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                  it.gbiagini.swm.iam.grpc.UserOuterClass.Credentials.getDefaultInstance()))
              .setResponseMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                  it.gbiagini.swm.iam.grpc.UserOuterClass.Response.getDefaultInstance()))
              .setSchemaDescriptor(new UserMethodDescriptorSupplier("registerUser"))
              .build();
        }
      }
    }
    return getRegisterUserMethod;
  }

  private static volatile io.grpc.MethodDescriptor<it.gbiagini.swm.iam.grpc.UserOuterClass.UpdateClaimsRequest,
      it.gbiagini.swm.iam.grpc.UserOuterClass.Response> getUpdateUserClaimsMethod;

  @io.grpc.stub.annotations.RpcMethod(
      fullMethodName = SERVICE_NAME + '/' + "updateUserClaims",
      requestType = it.gbiagini.swm.iam.grpc.UserOuterClass.UpdateClaimsRequest.class,
      responseType = it.gbiagini.swm.iam.grpc.UserOuterClass.Response.class,
      methodType = io.grpc.MethodDescriptor.MethodType.UNARY)
  public static io.grpc.MethodDescriptor<it.gbiagini.swm.iam.grpc.UserOuterClass.UpdateClaimsRequest,
      it.gbiagini.swm.iam.grpc.UserOuterClass.Response> getUpdateUserClaimsMethod() {
    io.grpc.MethodDescriptor<it.gbiagini.swm.iam.grpc.UserOuterClass.UpdateClaimsRequest, it.gbiagini.swm.iam.grpc.UserOuterClass.Response> getUpdateUserClaimsMethod;
    if ((getUpdateUserClaimsMethod = UserGrpc.getUpdateUserClaimsMethod) == null) {
      synchronized (UserGrpc.class) {
        if ((getUpdateUserClaimsMethod = UserGrpc.getUpdateUserClaimsMethod) == null) {
          UserGrpc.getUpdateUserClaimsMethod = getUpdateUserClaimsMethod =
              io.grpc.MethodDescriptor.<it.gbiagini.swm.iam.grpc.UserOuterClass.UpdateClaimsRequest, it.gbiagini.swm.iam.grpc.UserOuterClass.Response>newBuilder()
              .setType(io.grpc.MethodDescriptor.MethodType.UNARY)
              .setFullMethodName(generateFullMethodName(SERVICE_NAME, "updateUserClaims"))
              .setSampledToLocalTracing(true)
              .setRequestMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                  it.gbiagini.swm.iam.grpc.UserOuterClass.UpdateClaimsRequest.getDefaultInstance()))
              .setResponseMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                  it.gbiagini.swm.iam.grpc.UserOuterClass.Response.getDefaultInstance()))
              .setSchemaDescriptor(new UserMethodDescriptorSupplier("updateUserClaims"))
              .build();
        }
      }
    }
    return getUpdateUserClaimsMethod;
  }

  private static volatile io.grpc.MethodDescriptor<it.gbiagini.swm.iam.grpc.UserOuterClass.Credentials,
      it.gbiagini.swm.iam.grpc.UserOuterClass.Response> getPreAuthenticateUserMethod;

  @io.grpc.stub.annotations.RpcMethod(
      fullMethodName = SERVICE_NAME + '/' + "preAuthenticateUser",
      requestType = it.gbiagini.swm.iam.grpc.UserOuterClass.Credentials.class,
      responseType = it.gbiagini.swm.iam.grpc.UserOuterClass.Response.class,
      methodType = io.grpc.MethodDescriptor.MethodType.UNARY)
  public static io.grpc.MethodDescriptor<it.gbiagini.swm.iam.grpc.UserOuterClass.Credentials,
      it.gbiagini.swm.iam.grpc.UserOuterClass.Response> getPreAuthenticateUserMethod() {
    io.grpc.MethodDescriptor<it.gbiagini.swm.iam.grpc.UserOuterClass.Credentials, it.gbiagini.swm.iam.grpc.UserOuterClass.Response> getPreAuthenticateUserMethod;
    if ((getPreAuthenticateUserMethod = UserGrpc.getPreAuthenticateUserMethod) == null) {
      synchronized (UserGrpc.class) {
        if ((getPreAuthenticateUserMethod = UserGrpc.getPreAuthenticateUserMethod) == null) {
          UserGrpc.getPreAuthenticateUserMethod = getPreAuthenticateUserMethod =
              io.grpc.MethodDescriptor.<it.gbiagini.swm.iam.grpc.UserOuterClass.Credentials, it.gbiagini.swm.iam.grpc.UserOuterClass.Response>newBuilder()
              .setType(io.grpc.MethodDescriptor.MethodType.UNARY)
              .setFullMethodName(generateFullMethodName(SERVICE_NAME, "preAuthenticateUser"))
              .setSampledToLocalTracing(true)
              .setRequestMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                  it.gbiagini.swm.iam.grpc.UserOuterClass.Credentials.getDefaultInstance()))
              .setResponseMarshaller(io.grpc.protobuf.ProtoUtils.marshaller(
                  it.gbiagini.swm.iam.grpc.UserOuterClass.Response.getDefaultInstance()))
              .setSchemaDescriptor(new UserMethodDescriptorSupplier("preAuthenticateUser"))
              .build();
        }
      }
    }
    return getPreAuthenticateUserMethod;
  }

  /**
   * Creates a new async stub that supports all call types for the service
   */
  public static UserStub newStub(io.grpc.Channel channel) {
    io.grpc.stub.AbstractStub.StubFactory<UserStub> factory =
      new io.grpc.stub.AbstractStub.StubFactory<UserStub>() {
        @java.lang.Override
        public UserStub newStub(io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
          return new UserStub(channel, callOptions);
        }
      };
    return UserStub.newStub(factory, channel);
  }

  /**
   * Creates a new blocking-style stub that supports unary and streaming output calls on the service
   */
  public static UserBlockingStub newBlockingStub(
      io.grpc.Channel channel) {
    io.grpc.stub.AbstractStub.StubFactory<UserBlockingStub> factory =
      new io.grpc.stub.AbstractStub.StubFactory<UserBlockingStub>() {
        @java.lang.Override
        public UserBlockingStub newStub(io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
          return new UserBlockingStub(channel, callOptions);
        }
      };
    return UserBlockingStub.newStub(factory, channel);
  }

  /**
   * Creates a new ListenableFuture-style stub that supports unary calls on the service
   */
  public static UserFutureStub newFutureStub(
      io.grpc.Channel channel) {
    io.grpc.stub.AbstractStub.StubFactory<UserFutureStub> factory =
      new io.grpc.stub.AbstractStub.StubFactory<UserFutureStub>() {
        @java.lang.Override
        public UserFutureStub newStub(io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
          return new UserFutureStub(channel, callOptions);
        }
      };
    return UserFutureStub.newStub(factory, channel);
  }

  /**
   */
  public static abstract class UserImplBase implements io.grpc.BindableService {

    /**
     */
    public void registerUser(it.gbiagini.swm.iam.grpc.UserOuterClass.Credentials request,
        io.grpc.stub.StreamObserver<it.gbiagini.swm.iam.grpc.UserOuterClass.Response> responseObserver) {
      asyncUnimplementedUnaryCall(getRegisterUserMethod(), responseObserver);
    }

    /**
     */
    public void updateUserClaims(it.gbiagini.swm.iam.grpc.UserOuterClass.UpdateClaimsRequest request,
        io.grpc.stub.StreamObserver<it.gbiagini.swm.iam.grpc.UserOuterClass.Response> responseObserver) {
      asyncUnimplementedUnaryCall(getUpdateUserClaimsMethod(), responseObserver);
    }

    /**
     */
    public void preAuthenticateUser(it.gbiagini.swm.iam.grpc.UserOuterClass.Credentials request,
        io.grpc.stub.StreamObserver<it.gbiagini.swm.iam.grpc.UserOuterClass.Response> responseObserver) {
      asyncUnimplementedUnaryCall(getPreAuthenticateUserMethod(), responseObserver);
    }

    @java.lang.Override public final io.grpc.ServerServiceDefinition bindService() {
      return io.grpc.ServerServiceDefinition.builder(getServiceDescriptor())
          .addMethod(
            getRegisterUserMethod(),
            asyncUnaryCall(
              new MethodHandlers<
                it.gbiagini.swm.iam.grpc.UserOuterClass.Credentials,
                it.gbiagini.swm.iam.grpc.UserOuterClass.Response>(
                  this, METHODID_REGISTER_USER)))
          .addMethod(
            getUpdateUserClaimsMethod(),
            asyncUnaryCall(
              new MethodHandlers<
                it.gbiagini.swm.iam.grpc.UserOuterClass.UpdateClaimsRequest,
                it.gbiagini.swm.iam.grpc.UserOuterClass.Response>(
                  this, METHODID_UPDATE_USER_CLAIMS)))
          .addMethod(
            getPreAuthenticateUserMethod(),
            asyncUnaryCall(
              new MethodHandlers<
                it.gbiagini.swm.iam.grpc.UserOuterClass.Credentials,
                it.gbiagini.swm.iam.grpc.UserOuterClass.Response>(
                  this, METHODID_PRE_AUTHENTICATE_USER)))
          .build();
    }
  }

  /**
   */
  public static final class UserStub extends io.grpc.stub.AbstractAsyncStub<UserStub> {
    private UserStub(
        io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
      super(channel, callOptions);
    }

    @java.lang.Override
    protected UserStub build(
        io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
      return new UserStub(channel, callOptions);
    }

    /**
     */
    public void registerUser(it.gbiagini.swm.iam.grpc.UserOuterClass.Credentials request,
        io.grpc.stub.StreamObserver<it.gbiagini.swm.iam.grpc.UserOuterClass.Response> responseObserver) {
      asyncUnaryCall(
          getChannel().newCall(getRegisterUserMethod(), getCallOptions()), request, responseObserver);
    }

    /**
     */
    public void updateUserClaims(it.gbiagini.swm.iam.grpc.UserOuterClass.UpdateClaimsRequest request,
        io.grpc.stub.StreamObserver<it.gbiagini.swm.iam.grpc.UserOuterClass.Response> responseObserver) {
      asyncUnaryCall(
          getChannel().newCall(getUpdateUserClaimsMethod(), getCallOptions()), request, responseObserver);
    }

    /**
     */
    public void preAuthenticateUser(it.gbiagini.swm.iam.grpc.UserOuterClass.Credentials request,
        io.grpc.stub.StreamObserver<it.gbiagini.swm.iam.grpc.UserOuterClass.Response> responseObserver) {
      asyncUnaryCall(
          getChannel().newCall(getPreAuthenticateUserMethod(), getCallOptions()), request, responseObserver);
    }
  }

  /**
   */
  public static final class UserBlockingStub extends io.grpc.stub.AbstractBlockingStub<UserBlockingStub> {
    private UserBlockingStub(
        io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
      super(channel, callOptions);
    }

    @java.lang.Override
    protected UserBlockingStub build(
        io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
      return new UserBlockingStub(channel, callOptions);
    }

    /**
     */
    public it.gbiagini.swm.iam.grpc.UserOuterClass.Response registerUser(it.gbiagini.swm.iam.grpc.UserOuterClass.Credentials request) {
      return blockingUnaryCall(
          getChannel(), getRegisterUserMethod(), getCallOptions(), request);
    }

    /**
     */
    public it.gbiagini.swm.iam.grpc.UserOuterClass.Response updateUserClaims(it.gbiagini.swm.iam.grpc.UserOuterClass.UpdateClaimsRequest request) {
      return blockingUnaryCall(
          getChannel(), getUpdateUserClaimsMethod(), getCallOptions(), request);
    }

    /**
     */
    public it.gbiagini.swm.iam.grpc.UserOuterClass.Response preAuthenticateUser(it.gbiagini.swm.iam.grpc.UserOuterClass.Credentials request) {
      return blockingUnaryCall(
          getChannel(), getPreAuthenticateUserMethod(), getCallOptions(), request);
    }
  }

  /**
   */
  public static final class UserFutureStub extends io.grpc.stub.AbstractFutureStub<UserFutureStub> {
    private UserFutureStub(
        io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
      super(channel, callOptions);
    }

    @java.lang.Override
    protected UserFutureStub build(
        io.grpc.Channel channel, io.grpc.CallOptions callOptions) {
      return new UserFutureStub(channel, callOptions);
    }

    /**
     */
    public com.google.common.util.concurrent.ListenableFuture<it.gbiagini.swm.iam.grpc.UserOuterClass.Response> registerUser(
        it.gbiagini.swm.iam.grpc.UserOuterClass.Credentials request) {
      return futureUnaryCall(
          getChannel().newCall(getRegisterUserMethod(), getCallOptions()), request);
    }

    /**
     */
    public com.google.common.util.concurrent.ListenableFuture<it.gbiagini.swm.iam.grpc.UserOuterClass.Response> updateUserClaims(
        it.gbiagini.swm.iam.grpc.UserOuterClass.UpdateClaimsRequest request) {
      return futureUnaryCall(
          getChannel().newCall(getUpdateUserClaimsMethod(), getCallOptions()), request);
    }

    /**
     */
    public com.google.common.util.concurrent.ListenableFuture<it.gbiagini.swm.iam.grpc.UserOuterClass.Response> preAuthenticateUser(
        it.gbiagini.swm.iam.grpc.UserOuterClass.Credentials request) {
      return futureUnaryCall(
          getChannel().newCall(getPreAuthenticateUserMethod(), getCallOptions()), request);
    }
  }

  private static final int METHODID_REGISTER_USER = 0;
  private static final int METHODID_UPDATE_USER_CLAIMS = 1;
  private static final int METHODID_PRE_AUTHENTICATE_USER = 2;

  private static final class MethodHandlers<Req, Resp> implements
      io.grpc.stub.ServerCalls.UnaryMethod<Req, Resp>,
      io.grpc.stub.ServerCalls.ServerStreamingMethod<Req, Resp>,
      io.grpc.stub.ServerCalls.ClientStreamingMethod<Req, Resp>,
      io.grpc.stub.ServerCalls.BidiStreamingMethod<Req, Resp> {
    private final UserImplBase serviceImpl;
    private final int methodId;

    MethodHandlers(UserImplBase serviceImpl, int methodId) {
      this.serviceImpl = serviceImpl;
      this.methodId = methodId;
    }

    @java.lang.Override
    @java.lang.SuppressWarnings("unchecked")
    public void invoke(Req request, io.grpc.stub.StreamObserver<Resp> responseObserver) {
      switch (methodId) {
        case METHODID_REGISTER_USER:
          serviceImpl.registerUser((it.gbiagini.swm.iam.grpc.UserOuterClass.Credentials) request,
              (io.grpc.stub.StreamObserver<it.gbiagini.swm.iam.grpc.UserOuterClass.Response>) responseObserver);
          break;
        case METHODID_UPDATE_USER_CLAIMS:
          serviceImpl.updateUserClaims((it.gbiagini.swm.iam.grpc.UserOuterClass.UpdateClaimsRequest) request,
              (io.grpc.stub.StreamObserver<it.gbiagini.swm.iam.grpc.UserOuterClass.Response>) responseObserver);
          break;
        case METHODID_PRE_AUTHENTICATE_USER:
          serviceImpl.preAuthenticateUser((it.gbiagini.swm.iam.grpc.UserOuterClass.Credentials) request,
              (io.grpc.stub.StreamObserver<it.gbiagini.swm.iam.grpc.UserOuterClass.Response>) responseObserver);
          break;
        default:
          throw new AssertionError();
      }
    }

    @java.lang.Override
    @java.lang.SuppressWarnings("unchecked")
    public io.grpc.stub.StreamObserver<Req> invoke(
        io.grpc.stub.StreamObserver<Resp> responseObserver) {
      switch (methodId) {
        default:
          throw new AssertionError();
      }
    }
  }

  private static abstract class UserBaseDescriptorSupplier
      implements io.grpc.protobuf.ProtoFileDescriptorSupplier, io.grpc.protobuf.ProtoServiceDescriptorSupplier {
    UserBaseDescriptorSupplier() {}

    @java.lang.Override
    public com.google.protobuf.Descriptors.FileDescriptor getFileDescriptor() {
      return it.gbiagini.swm.iam.grpc.UserOuterClass.getDescriptor();
    }

    @java.lang.Override
    public com.google.protobuf.Descriptors.ServiceDescriptor getServiceDescriptor() {
      return getFileDescriptor().findServiceByName("User");
    }
  }

  private static final class UserFileDescriptorSupplier
      extends UserBaseDescriptorSupplier {
    UserFileDescriptorSupplier() {}
  }

  private static final class UserMethodDescriptorSupplier
      extends UserBaseDescriptorSupplier
      implements io.grpc.protobuf.ProtoMethodDescriptorSupplier {
    private final String methodName;

    UserMethodDescriptorSupplier(String methodName) {
      this.methodName = methodName;
    }

    @java.lang.Override
    public com.google.protobuf.Descriptors.MethodDescriptor getMethodDescriptor() {
      return getServiceDescriptor().findMethodByName(methodName);
    }
  }

  private static volatile io.grpc.ServiceDescriptor serviceDescriptor;

  public static io.grpc.ServiceDescriptor getServiceDescriptor() {
    io.grpc.ServiceDescriptor result = serviceDescriptor;
    if (result == null) {
      synchronized (UserGrpc.class) {
        result = serviceDescriptor;
        if (result == null) {
          serviceDescriptor = result = io.grpc.ServiceDescriptor.newBuilder(SERVICE_NAME)
              .setSchemaDescriptor(new UserFileDescriptorSupplier())
              .addMethod(getRegisterUserMethod())
              .addMethod(getUpdateUserClaimsMethod())
              .addMethod(getPreAuthenticateUserMethod())
              .build();
        }
      }
    }
    return result;
  }
}
