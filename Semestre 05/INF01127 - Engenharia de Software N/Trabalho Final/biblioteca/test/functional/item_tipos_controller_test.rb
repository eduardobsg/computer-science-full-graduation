require 'test_helper'

class ItemTiposControllerTest < ActionController::TestCase
  setup do
    @item_tipo = item_tipos(:one)
  end

  test "should get index" do
    get :index
    assert_response :success
    assert_not_nil assigns(:item_tipos)
  end

  test "should get new" do
    get :new
    assert_response :success
  end

  test "should create item_tipo" do
    assert_difference('ItemTipo.count') do
      post :create, :item_tipo => @item_tipo.attributes
    end

    assert_redirected_to item_tipo_path(assigns(:item_tipo))
  end

  test "should show item_tipo" do
    get :show, :id => @item_tipo.to_param
    assert_response :success
  end

  test "should get edit" do
    get :edit, :id => @item_tipo.to_param
    assert_response :success
  end

  test "should update item_tipo" do
    put :update, :id => @item_tipo.to_param, :item_tipo => @item_tipo.attributes
    assert_redirected_to item_tipo_path(assigns(:item_tipo))
  end

  test "should destroy item_tipo" do
    assert_difference('ItemTipo.count', -1) do
      delete :destroy, :id => @item_tipo.to_param
    end

    assert_redirected_to item_tipos_path
  end
end
