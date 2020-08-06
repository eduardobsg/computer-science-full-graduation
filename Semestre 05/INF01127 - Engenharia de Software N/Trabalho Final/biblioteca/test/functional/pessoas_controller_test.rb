require 'test_helper'

class PessoasControllerTest < ActionController::TestCase
  setup do
    @pessoa = pessoas(:one)
  end

  test "should get index" do
    get :index
    assert_response :success
    assert_not_nil assigns(:pessoas)
  end

  test "should get new" do
    get :new
    assert_response :success
  end

  test "should create pessoa" do
    assert_difference('Pessoa.count') do
      post :create, :pessoa => @pessoa.attributes
    end

    assert_redirected_to pessoa_path(assigns(:pessoa))
  end

  test "should show pessoa" do
    get :show, :id => @pessoa.to_param
    assert_response :success
  end

  test "should get edit" do
    get :edit, :id => @pessoa.to_param
    assert_response :success
  end

  test "should update pessoa" do
    put :update, :id => @pessoa.to_param, :pessoa => @pessoa.attributes
    assert_redirected_to pessoa_path(assigns(:pessoa))
  end

  test "should destroy pessoa" do
    assert_difference('Pessoa.count', -1) do
      delete :destroy, :id => @pessoa.to_param
    end

    assert_redirected_to pessoas_path
  end
end
