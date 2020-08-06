class ItemTiposController < ApplicationController
  # GET /item_tipos
  # GET /item_tipos.xml
  def index
    @item_tipos = ItemTipo.all

    respond_to do |format|
      format.html # index.html.erb
      format.xml  { render :xml => @item_tipos }
    end
  end

  # GET /item_tipos/1
  # GET /item_tipos/1.xml
  def show
    @item_tipo = ItemTipo.find(params[:id])

    respond_to do |format|
      format.html # show.html.erb
      format.xml  { render :xml => @item_tipo }
    end
  end

  # GET /item_tipos/new
  # GET /item_tipos/new.xml
  def new
    @item_tipo = ItemTipo.new

    respond_to do |format|
      format.html # new.html.erb
      format.xml  { render :xml => @item_tipo }
    end
  end

  # GET /item_tipos/1/edit
  def edit
    @item_tipo = ItemTipo.find(params[:id])
  end

  # POST /item_tipos
  # POST /item_tipos.xml
  def create
    @item_tipo = ItemTipo.new(params[:item_tipo])

    respond_to do |format|
      if @item_tipo.save
        format.html { redirect_to(@item_tipo, :notice => 'Item tipo was successfully created.') }
        format.xml  { render :xml => @item_tipo, :status => :created, :location => @item_tipo }
      else
        format.html { render :action => "new" }
        format.xml  { render :xml => @item_tipo.errors, :status => :unprocessable_entity }
      end
    end
  end

  # PUT /item_tipos/1
  # PUT /item_tipos/1.xml
  def update
    @item_tipo = ItemTipo.find(params[:id])

    respond_to do |format|
      if @item_tipo.update_attributes(params[:item_tipo])
        format.html { redirect_to(@item_tipo, :notice => 'Item tipo was successfully updated.') }
        format.xml  { head :ok }
      else
        format.html { render :action => "edit" }
        format.xml  { render :xml => @item_tipo.errors, :status => :unprocessable_entity }
      end
    end
  end

  # DELETE /item_tipos/1
  # DELETE /item_tipos/1.xml
  def destroy
    @item_tipo = ItemTipo.find(params[:id])
    @item_tipo.destroy

    respond_to do |format|
      format.html { redirect_to(item_tipos_url) }
      format.xml  { head :ok }
    end
  end
end
