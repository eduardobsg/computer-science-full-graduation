require 'test_helper'

class PessoaTiposControllerTest < ActionController::TestCase
  setup do
    @pessoa_tipo = pessoa_tipos(:one)
  end

  test "should get index" do
    get :index
    assert_response :success
    assert_not_nil assigns(:pessoa_tipos)
  end

  test "should get new" do
    get :new
    assert_response :success
  end

  test "should create pessoa_tipo" do
    assert_difference('PessoaTipo.count') do
      post :create, :pessoa_tipo => @pessoa_tipo.attributes
    end

    assert_redirected_to pessoa_tipo_path(assigns(:pessoa_tipo))
  end

  test "should show pessoa_tipo" do
    get :show, :id => @pessoa_tipo.to_param
    assert_response :success
  end

  test "should get edit" do
    get :edit, :id => @pessoa_tipo.to_param
    assert_response :success
  end

  test "should update pessoa_tipo" do
    put :update, :id => @pessoa_tipo.to_param, :pessoa_tipo => @pessoa_tipo.attributes
    assert_redirected_to pessoa_tipo_path(assigns(:pessoa_tipo))
  end

  test "should destroy pessoa_tipo" do
    assert_difference('PessoaTipo.count', -1) do
      delete :destroy, :id => @pessoa_tipo.to_param
    end

    assert_redirected_to pessoa_tipos_path
  end
end
